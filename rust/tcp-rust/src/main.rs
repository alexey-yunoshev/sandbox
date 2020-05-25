use std::collections::HashMap;
use std::net::Ipv4Addr;

mod tcp;

static IPV4: u16 = 0x800;
static TCP: u8 = 0x06;


#[derive(Hash, Eq, PartialEq, Debug, Clone, Copy)]
struct Quad {
    src: (Ipv4Addr, u16),
    dst: (Ipv4Addr, u16),
}

fn main() -> std::io::Result<()> {
    let mut connections: HashMap<Quad, tcp::Connection> = Default::default();
    let mut nic = tun_tap::Iface::without_packet_info("tun0", tun_tap::Mode::Tun)
    .expect("failed to create nic");
    let mut buf = [0u8; 1504];
    loop {
        let nbytes = nic.recv(&mut buf[..]).expect("faield to rcv nic");
        // let eth_proto = u16::from_be_bytes([buf[2], buf[3]]);
        // if eth_proto != IPV4 {
        //     continue;
        // }
        match etherparse::Ipv4HeaderSlice::from_slice(&buf[..nbytes]) {
            Ok(ip_header) => {
                let src = ip_header.source_addr();
                let dst = ip_header.destination_addr();

                if ip_header.protocol() != TCP {
                    continue;
                }

                let ip_header_size = ip_header.slice().len();
                match etherparse::TcpHeaderSlice::from_slice(&buf[ip_header_size..nbytes]) {
                    Ok(tcp_header) => {
                        use std::collections::hash_map::Entry;

                        let data_offset = ip_header_size + tcp_header.slice().len();
                        match connections.entry(Quad {
                            src: (src, tcp_header.source_port()),
                            dst: (dst, tcp_header.destination_port()),
                        }) {
                            Entry::Occupied(mut c) => {
                                c.get_mut().on_packet(
                                    &mut nic,
                                    ip_header,
                                    tcp_header,
                                    &buf[data_offset..nbytes],
                                ).expect("error");
                            }
                            Entry::Vacant(mut e) => {
                                if let Some(c) = tcp::Connection::accept(
                                    &mut nic,
                                    ip_header,
                                    tcp_header,
                                    &buf[data_offset..nbytes],
                                )? {
                                    e.insert(c);
                                }
                            }
                        }
                    },
                    Err(e) => {
                        eprintln!("ignoring weird tcp/ip packet {:?}", e);
                    }
                }
            }
            Err(_e) => {
                eprintln!("ignoring weird ip packet");
            }
        }
        // let mut data = [0; 1500];
        // data.copy_from_slice(&buf[4..nbytes]);
    }
}
