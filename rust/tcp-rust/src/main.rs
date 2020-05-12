fn main() {
    let nic = tun_tap::Iface::new("tun0", tun_tap::Mode::Tun)
        .expect("failed to create nic");
    let mut buf = [0u8; 1504];
    loop {
        let nbytes = nic.recv(&mut buf[..]).expect("faield to rcv nic");
        eprintln!("hello");
        let eth_proto = u16::from_be_bytes([buf[2], buf[3]]);
        if eth_proto != 0x800 {
            continue;
        }
        match etherparse::Ipv4HeaderSlice::from_slice(&buf[4..nbytes]) {
            Ok(packet) => {
                let src = packet.source_addr();
                let dest = packet.destination_addr();
                let proto = packet.protocol();
                eprintln!("{} -> {} {} bytes, proto: {}",
                src,
                dest,
                packet.payload_len(),
                proto,
            );
            },
            Err(_e) => {
                eprintln!("ignoring weird packet");
            },
        }
        // let mut data = [0; 1500];
        // data.copy_from_slice(&buf[4..nbytes]);
    }
   }
