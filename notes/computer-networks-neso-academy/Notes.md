# Neso Academy. Computer Networks

> [YouTube Course](https://www.youtube.com/watch?v=VwN91x5i25g&list=PLBlnK6fEyqRgMCUAG0XRw78UA8qnv6jEx&index=1)

<!-- toc start -->

- [1. Intro](#1.-intro)
- [2. Basic Characteristic](#2.-Basic-Characteristics)
- [3. Network Protocols & Communications (Part 1)](#3.-Network-Protocols-&-Communications)
- [4. Components of a Computer Network](#4.-Components-of-a-Computer-Network)
- [5. Classification of Computer Networks](#5.-Classification-of-Computer-Networks)
- [6. Network Topology](#6.-Network-Topology)
- [7. Basics of IP Addressing](#7.-Basics-of-IP-Addressing)
- [8. Basics of Port Addressing](#8.-Basics-of-Port-Addressing)
- [9. Switching Techniques in Computer Networks](#9.-Switching-Techniques-in-Computer-Networks)
- [10. Layering in Computer Networks](#10.-Layering-in-Computer-Networks)

<!-- toc end -->


# 1. Intro

Computer networks are __nodes__ connected by __links__, where node
are devices that are able to send and receive data. There
are __end__ nodes and __intermediary__ nodes.

# 2. Basic Characteristics

- Fault tolerance
- Scalability
- Quality of Service
- Security

# 3. Network Protocols & Communications

__Data communication__ through a link (__transmission medium__).

Data flows:
- Simplex (unidirectional). Keyboard
- Half Duplex (both directions but not at the same time). Walki-talkie
- Full Duplex (both directions at the same time). Telephone line

Elements of communication:
- Source
- Sender
- Media
- Protocols

Elements of protocol:
- message encoding
- message formatting and encapsulation
- message timing
- message size
- message delivery options

Message delivery options:
- Unicast (one sender - one reciever)
- Multicast (one sender - several recievers)
- Broadcast (one sender - all recievers)

# 4. Components of a Computer Network

- Node
  - End nodes
  - Intermediary nodes
- Media
  - wired
  - wireless
- Servies
  - email
  - storage
  - file sharing...

# 5. Classification of Computer Networks
 - Local Area (LAN)
 - Metropolitan Area (MAN)
 - Wide Area (WAN)

# 6. Network Topology

Arrangement of nodes of a computer network, a layout

- Physical topology - node placement
- Logical topology - data flow in the network

Topologies
 - Bus. Everyone receives a signal, but only the intended receiver
   accepts it. __Common transmission medium__

   ![bus topology](https://cdn.comparitech.com/wp-content/uploads/2018/11/Bus-Topology.jpg "bus topology")
 
 - Ring. A bus topology in a closed loop.

   ![ring topology](https://cdn.comparitech.com/wp-content/uploads/2018/11/Ring-Topology.jpg "ring topology")
 
 - Star
  
   ![star](https://cdn.comparitech.com/wp-content/uploads/2018/11/star-Topology.jpg "star")

 - Mesh

   ![mesh](https://cdn.comparitech.com/wp-content/uploads/2018/11/Mesh-Topology.jpg "mesh")
 - Hybrid

# 7. Basics of IP Addressing

__IP__ addrs:
logic, can be changed, more like a location

__MAC__ - Media Access Control. Unique hardware address

# 8. Basics of Port Addressing

So three pieces are necesssary for addressing:
Ip addr (location), Mac addr (host withing LAN), Port (process within host)

# 9. Switching Techniques in Computer Networks

__Switching__ in computer network helps in deciding the best
route for data transmission if there are multiple paths in a
larger network

- Circuit Switching

  Circuit switching is a method of implementing a telecommunications network in which two network nodes establish a dedicated communications channel (circuit) through the network before the nodes may communicate. The circuit guarantees the full bandwidth of the channel and remains connected for the duration of the communication session.

- Message Switching

  In telecommunications, message switching involves messages routed in their entirety, one hop at a time. It evolved from circuit switching and was the precursor of packet switching.

- Packet Switching
  - Datagram Approach
  - Virtual Circuit Approach

# 10. Layering in Computer Networks

__OSI__ Open System Interconnection, (ISO 7498) a joint ISO and ITU-T standard for computer networks and communication protocols

Layers:
1. Physical Layer
1. Data Link Layer
1. Network Layer
1. Transport Layer
1. Session Layer
1. Presentation Layer
1. Application Layer

# 11. Devices

A network __switch__ is networking hardware that connects devices on a computer network by using packet switching to receive and forward data to the destination device. A network switch is a multiport network bridge that uses MAC addresses to forward data at the data link layer (layer 2) of the OSI model. Unlike less advanced repeater __hubs__, which broadcast the same data out of each of its ports and let the devices decide what data they need, a network switch forwards data only to the devices that need to receive it.

A __router__ is a networking device that forwards data packets between computer networks. Routers perform the traffic directing functions on the Internet. Data sent through the internet, such as a web page or email, is in the form of data packets. A packet is typically forwarded from one router to another router through the networks that constitute an internetwork (e.g. the Internet) until it reaches its destination node.

In telecommunications, a __repeater__ is an electronic device that receives a signal and retransmits it. Repeaters are used to extend transmissions so that the signal can cover longer distances or be received on the other side of an obstruction. Some types of repeaters broadcast an identical signal, but alter its method of transmission, for example, on another frequency or baud rate.

A __bridge__ is a device that creates a single aggregate network from multiple communication networks or network segments. This function is called network bridging. Bridging is distinct from routing. Routing allows multiple networks to communicate independently and yet remain separate, whereas bridging connects two separate networks as if they were a single network.

# 12 Physical Layer
In signal processing, a __signal__ is a function that conveys information about a phenomenon. In electronics and telecommunications, it refers to any time varying voltage, current or electromagnetic wave that carries information. A signal may also be defined as an observable change in a quality such as quantity.

Kinds:
- Analog

  Any value. All real-life signals are analog
  An analog signal is any continuous signal for which the time varying feature of the signal is a representation of some other time varying quantity, i.e., analogous to another time varying signal. For example, in an analog audio signal, the instantaneous voltage of the signal varies continuously with the sound pressure.

- Digital

  A digital signal is a signal that is constructed from a discrete set of waveforms of a physical quantity so as to represent a sequence of discrete values

Link configuration:
- point-to-point
- multipoint

# 13 Data Link Layer

The data link layer, or layer 2, is the second layer of the seven-layer OSI model of computer networking. This layer is the protocol layer that transfers data between adjacent network nodes in a wide area network (WAN) or between nodes on the same local area network (LAN) segment. The data link layer provides the functional and procedural means to transfer data between network entities and might provide the means to detect and possibly correct errors that may occur in the physical layer.

The data link layer is concerned with local delivery of frames between nodes on the same level of the network. Data-link frames, as these protocol data units are called, do not cross the boundaries of a local area network. Inter-network routing and global addressing are higher-layer functions, allowing data-link protocols to focus on local delivery, addressing, and media arbitration.

# 14 Error Detection

- __VRC__ (Vertical Redundancy Check)

  Also, parity check.
  Redundant/parity/VRC bit = Odd number of 1's ? 1 : 0

- __LRC__ (Longitudinal Redundancy Check)

  Two dimensional. Adds a redundancy block with the same
  principal as above.

- __Checksum__

  
- __CRC__

# 15 Network Performance

- Bandwith

  In computing, bandwidth is the maximum rate of data transfer  across a given path. Bandwidth may be characterized as   network bandwidth, data bandwidth, or digital bandwidth.

- Throughput

  May be the reality.
  In general terms, throughput is the rate of production or the rate at which something is processed.

- Latency/delay

  The delay of a network specifies how long it takes for a bit of data to travel across the network from one communication endpoint to another.

  - Processing delay – time it takes router to process the packet header
  - Queuing delay – time the packet spends in routing queues
  - Transmission delay – time it takes to push the packet's bits onto the link
  - Propagation delay – time for a signal to reach its destination


In data communications, the __bandwidth-delay__ product is the product of a data link's capacity (in bits per second) and its round-trip delay time (in seconds). The result, an amount of data measured in bits (or bytes), is equivalent to the maximum amount of data on the network circuit at any given time, i.e., data that has been transmitted but not yet acknowledged

# 17 Flow control

__Automatic repeat request (ARQ)__, also known as automatic repeat query, is an error-control method for data transmission that uses acknowledgements (messages sent by the receiver indicating that it has correctly received a packet) and timeouts (specified periods of time allowed to elapse before an acknowledgment is to be received) to achieve reliable data transmission over an unreliable service.

Protocols:
- Noiseless Channels
  - Simplest
  - Stop-and-wait

    Send a frame. Wait for ack. Send another. Wait for ack...

- Noisy channels
  - Stop-and-wait ARQ


  - Go-Back-N-ARQ
  - Selective Repeat ARQ

__Sliding window__ protocols allow a selected number of packets, the window, to be sent without having to wait for an ACK. Each packet receives a sequence number, and the ACKs send back that number. The protocol keeps track of which packets have been ACKed, and when they are received, sends more packets. In this way, the window slides along the stream of packets making up the transfer.


# 18 Multiple Access Protocols
  A __collision__ is the situation that occurs when two or more demands are made simultaneously on equipment that can handle only one at any given instant

- Random Access Protocols

  All stations have the same priority, which may lead to higher possibilty of collisions.

  - ALOHA

    Pure Aloha
    Any station can transmit data at any time. Wait for ack. If no ack within set timeout, sends the same frame in a random amount of time to prevent collision

    Slotted Aloha
    Stations can transmit data only at the beginning of any time slot, which are fixed.

  - CSMA

    __Carrier-sense multiple access__ (CSMA) is a media access control (MAC) protocol in which a node verifies the absence of other traffic before transmitting on a shared transmission medium, such as an electrical bus or a band of the electromagnetic spectrum.

  - CSMA/CD (CSMA with Collision Detection)
  - CSMA/CA (CSMA with Collision Avoidance)


- Controlled Access protocols

The stations consult one another to find which station has the right to send.

  - Reservation
  - Polling
  - Token passing

- Channelization Protocols

The available bandwidth is shared on time, frequency, ot through code between different stations.

  - FDMA
  - TDMA
  - CDMA