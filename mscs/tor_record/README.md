The TOR protocol
================

TOR (citation [8] in our paper) aims to guarantee privacy by utilizing the
onion routing.

<img src="tor_record.jpg"></img>

Recall that after the TOR establishment protocol, all the entities (except
a server <img src="https://latex.codecogs.com/gif.latex?D" /> maintain
states (a symmetric key and a forward/backword routing information) identified 
with connection ID (connID), which would be used in the TOR record protocol.

When an endpoint wants to send a payload <img
src="https://latex.codecogs.com/gif.latex?p"/>,
he/she sends <img src="https://latex.codecogs.com/gif.latex?p" /> with
a connID.

When a TOR relay <img src="https://latex.codecogs.com/gif.latex?B" /> receives 
<img src="https://latex.codecogs.com/gif.latex?msg"/>
encrypted with <img src="https://latex.codecogs.com/gif.latex?k_{AC}" /> and
<img src="https://latex.codecogs.com/gif.latex?k_{AB}" />
and a connID, it fetches a state with the connID, decrypts an onion-encrypted
message, and sends the resultant message to the next hop.
