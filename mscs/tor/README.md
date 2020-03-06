The TOR protocol
================

TOR (citation [8] in our paper) aims to guarantee privacy by utilizing the
onion routing.

The followings are two simple MSCs. One is the protocol with a read-only
middlebox and the other is with a read/write middlebox.

The TOR establishment protocol
------------------------------
<img src="tor_establishment.jpg"></img>

The following MAC keys are established at the mcTLS handshake protocol.
Note that a read MAC key is also used as an encryption key.

&nbsp;&nbsp;<img src="https://latex.codecogs.com/gif.latex?k_r"/>:
a read MAC key<br>
&nbsp;&nbsp;<img src="https://latex.codecogs.com/gif.latex?k_w"/>:
a write MAC key<br>
&nbsp;&nbsp;<img src="https://latex.codecogs.com/gif.latex?k_e"/>:
an endpoint MAC key<br>

When an endpoint sends want to send a payload <img
src="https://latex.codecogs.com/gif.latex?p"/>,
he/she generates three MACs (a read MAC, a write MAC, and an endpoint MAC) and
send them with <img src="https://latex.codecogs.com/gif.latex?p" /> as <img
src="https://latex.codecogs.com/gif.latex?msg" />.

When a read-only middlebox that has only <img
src="https://latex.codecogs.com/gif.latex?k_r" /> receives a <img
src="https://latex.codecogs.com/gif.latex?msg" />,
it verifies a read MAC to check whether there is a third-party modification and 
then functions based on <img src="https://latex.codecogs.com/gif.latex?p" /> if
it there is no invalid modification.


The TOR record protocol
-----------------------
<img src="tor_record.jpg"></img>

The following MAC keys are established at the mcTLS handshake protocol.
Note that a read MAC key is also used as an encryption key.

&nbsp;&nbsp;<img src="https://latex.codecogs.com/gif.latex?k_r"/>:
a read MAC key<br>
&nbsp;&nbsp;<img src="https://latex.codecogs.com/gif.latex?k_w"/>:
a write MAC key<br>
&nbsp;&nbsp;<img src="https://latex.codecogs.com/gif.latex?k_e"/>:
an endpoint MAC key<br>

When an endpoint sends want to send a payload <img
src="https://latex.codecogs.com/gif.latex?p"/>,
he/she generates three MACs (a read MAC, a write MAC, and an endpoint MAC) and
send them with <img src="https://latex.codecogs.com/gif.latex?p" /> as <img
src="https://latex.codecogs.com/gif.latex?msg" />.

When a read/write middlebox that has both <img
src="https://latex.codecogs.com/gif.latex?k_r" /> and <img
src="https://latex.codecogs.com/gif.latex?k_w" /> receives a <img
src="https://latex.codecogs.com/gif.latex?msg" />,
it verifies a read MAC as well as a write MAC to check whether there is any 
modification by a thrid-party or a read-only middlebox and 
then functions based on <img src="https://latex.codecogs.com/gif.latex?p" />
and modifies it into <img src="https://latex.codecogs.com/gif.latex?p'" /> if
there is no invalid modification.

Note that a receiving endpoint would find an invalid endpoint MAC, since
a read/write middlebox cannot generate an endpoint MAC on <img
src="https://latex.codecogs.com/gif.latex?p'" />. Nevertheless, if a write MAC is
valid, this means there was a valid modification on the path.
