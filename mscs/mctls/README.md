Multi-context TLS (mcTLS)
=========================

Multi-context TLS (mcTLS) (citation [6] in our paper) aims to introduce 
middleboxes while giving them read/write permission.

This is feasible with three MAC keys -- a read MAC key, a write MAC key, and an
endpoint MAC key. A read-only middlebox only receives a read MAC key from
endpoints while a read/write middlebox gets both a read MAC key and a write MAC
key.

Note that there is no way to detect a skipping attack in mcTLS.

The mcTLS record protocol with a read-only middlebox
----------------------------------------------------
<img src="mctls_record_reader.jpg"></img>


The mcTLS record protocol with a read/write middlebox
-----------------------------------------------------
<img src="mctls_record_writer.jpg"></img>
