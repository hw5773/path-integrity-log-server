The TOR protocol
================

TOR (citation [8] in our paper) aims to guarantee privacy by utilizing the
onion routing.

<img src="tor_establishment.jpg"></img>

The above MSC describes a procedure of extending a circuit to <img
src="https://latex.codecogs.com/gif.latex?C" />.
Here, <img src="https://latex.codecogs.com/gif.latex?A" /> is a client, <img
src="https://latex.codecogs.com/gif.latex?B" /> and <img
src="https://latex.codecogs.com/gif.latex?C" />, and <img
src="https://latex.codecogs.com/gif.latex?D" /> is a intended server.
Note that <img src="https://latex.codecogs.com/gif.latex?k_{AB}" /> is a shared
key between <img src="https://latex.codecogs.com/gif.latex?A" /> and <img
src="https://latex.codecogs.com/gif.latex?B" /> before this extension.

During the TOR establishment protocol, a client establishes a shared key with
a TOR relay by using a DH key exchange. Finally, all the entities (except
a server <img src="https://latex.codecogs.com/gif.latex?D" /> maintain
states (a symmetric key and a forward/backword routing information) identified 
with connection ID (connID), which would be used in the TOR record protocol.
