[Lectures](https://www.youtube.com/watch?v=5D67Qy1tPLY&list=PLLFIgriuZPAcCkmSTfcq7oaHcVy3rzEtc)

[Book](https://eclass.teicrete.gr/modules/document/file.php/TP326/%CE%98%CE%B5%CF%89%CF%81%CE%AF%CE%B1%20(Lectures)/Computer_Networking_A_Top-Down_Approach.pdf)

# 1. What is the Internet

1. Hosts
1. Links
1. Routers
1. Protocols

An infrastructure that provides services to applications.

## 1.2 The Network Edge
Hosts, end systems, data centers.
__Access network__ physically connects an end system to the first route (also known as the “edge router”) on a path from the end system to any other distant end system.

Physical media fall into two categories: __guided media__ and __unguided media__. With guided media, the waves are guided along a solid medium, such as a fiber-optic cable, a twisted-pair copper wire, or a coaxial cable. With unguided media, the waves propagate in the atmosphere and in outer space, such as in a wireless LAN or a digital satellite channel.

Twisted-Pair Copper Wire, Coaxial Cable, Fiber Optics, Terrestrial Radio Channels, Satellite Radio Channels

## 1.3 The Network Core
### Packet Switching
Packets are transmitted over each communication link at a rate equal to the full transmission rate of the link.

For each attached link, the packet switch has an __output buffer__ (also called an output queue), which stores packets that the router is about to send into that link.

Each router has a __forwarding table__ that maps destination addresses (or portions of the destination addresses) to that router’s outbound links.

### Network of networks

A _PoP_ (points of presence) is simply a group of one or more routers (at the same location) in the provider’s network where customer ISPs can connect into the provider ISP.

Any ISP (except for tier-1 ISPs) may choose to __multi-home__, that is, to connect to two or more provider ISPs so that it can continue to send and receive packets into the Internet even if one of its providers has a failure.

A third-party company can create an __Internet Exchange Point (IXP)__ (typically in a stand-alone building with its own switches), which is a meeting point where multiple ISPs can __peer__ together.

## 1.4 Delay, Loss, Throughput

__Delay__:
- processing (header parsing, error checking)
- queuing
- transmission

  This is the amount of time required to push (that is, transmit) all of the packet’s bits into the link.

- propagation

  That is, the propagation delay is d/s, where d is the   distance between router Aand router B and s is the   propagation speed of the link.

# Transport Layer

This job of delivering the data in a transport-layer segment to the correct socket is called __demultiplexing__.
The job of gathering data chunks at the source host from different sockets, encapsulating each data chunk with header information (that will later be used in demultiplexing) to create segments, and passing the segments to the network layer is called __multiplexing__.

It is important to note that a __UDPsocket is fully identified by a two-tuple consisting of a destination IPaddress and a destination port number__. As a consequence, if two UDPsegments have different source IPaddresses and/or source port numbers, but have the same destination IPaddress and destination port number, then the two segments will be directed to the same destination process via the same destination socket.



https://youtu.be/OlbQ88lx7J0?t=748
Computer Networking A Top-Down Approach 6th Edition 49

