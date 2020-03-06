Multi-context TLS (mcTLS)
=========================

Multi-context TLS (mcTLS) (citation [6] in our paper) aims to introduce 
middleboxes while giving them read/write permission.

This is feasible with three MAC keys -- a read MAC key, a write MAC key, and an
endpoint MAC key. A read-only middlebox only receives a read MAC key from
endpoints while a read/write middlebox gets both a read MAC key and a write MAC
key.

Note that there is no way to detect a skipping attack in mcTLS.
The followings are two simple MSCs. One is the protocol with a read-only
middlebox and the other is with a read/write middlebox.

The mcTLS record protocol with a read-only middlebox
----------------------------------------------------
<img src="mctls_record_reader.jpg"></img>

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


The mcTLS record protocol with a read/write middlebox
-----------------------------------------------------
<img src="mctls_record_writer.jpg"></img>

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
then functions based on <img src="https://latex.codecogs.com/gif.latex?p" /> if
there is no invalid modification.

