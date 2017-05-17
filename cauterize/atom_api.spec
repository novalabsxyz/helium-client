(name "atom_api")
(version "1.0.0")
(fingerprint 8ad8933c3f4f010d11107026e0b97b6c7e3c448a)
(size 1 110)
(depth 8)
(typelength 2)
(lengthtag t1)
(type 
  res_send
  enumeration
  (fingerprint cf96ce11bb83a824200185883b247330c7ecdf06)
  (size 1 1)
  (depth 1)
  t1
  (values 
    (value ok 0)
    (value err_not_connected 1)
    (value err_dropped 2)
    (value err_nack 3)
    (value err_channel_access 4)))
(type 
  res_info
  record
  (fingerprint 91aa1322010ca6f3756d0aaa2d198eb2dea550dc)
  (size 21 21)
  (depth 2)
  (fields 
    (field mac 0 u64)
    (field uptime 1 u32)
    (field time 2 u32)
    (field fw_version 3 u32)
    (field radio_count 4 u8)))
(type 
  res_connect
  enumeration
  (fingerprint 36b7ee9ed164e05cf473ab3740161b0f2690f787)
  (size 1 1)
  (depth 1)
  t1
  (values (value ok 0) (value err_fallback_to_slow_connect 1)))
(type 
  frame_app
  vector
  (fingerprint 980a97151e6b90b3f6d41e6c55ac92889c16a179)
  (size 1 104)
  (depth 2)
  u8
  103
  t1)
(type 
  poll_frame
  union
  (fingerprint 5925f725fe35a8756ed7103719d2183b10b97319)
  (size 1 105)
  (depth 3)
  t1
  (fields (empty none 0) (field frame 1 frame_app)))
(type 
  res_poll
  record
  (fingerprint fe3beaf44b49c8e50587dcf402eaf1ceef6551cd)
  (size 2 106)
  (depth 4)
  (fields (field needs_reset 0 bool) (field frame 1 poll_frame)))
(type 
  cmd_send
  union
  (fingerprint 0f2599b0b255ef276289bc4314aa386c1d5a7ac0)
  (size 2 105)
  (depth 3)
  t1
  (fields (field req 0 frame_app) (field res 1 res_send)))
(type 
  cmd_poll
  union
  (fingerprint 563927f357008d8f9b0c7971ad4e0b750e31b4aa)
  (size 1 107)
  (depth 5)
  t1
  (fields (empty req 0) (field res 1 res_poll)))
(type 
  cmd_mac
  union
  (fingerprint 28caed1772fb1c68aade8b3c4ba6abdc1bfd4981)
  (size 1 9)
  (depth 2)
  t1
  (fields (empty req 0) (field res 1 u64)))
(type 
  cmd_info
  union
  (fingerprint 141eaf55c7af6f09246fd689fca3b18ab09e1a50)
  (size 1 22)
  (depth 3)
  t1
  (fields (empty req 0) (field res 1 res_info)))
(type 
  cmd_connected
  union
  (fingerprint 1c7194af95e673281ade842ca04c55a97716f29c)
  (size 1 2)
  (depth 2)
  t1
  (fields (empty req 0) (field res 1 bool)))
(type 
  arr_u8_32
  array
  (fingerprint 5051077de0f3755b22b9aafa6ba8fb38fed601ff)
  (size 32 32)
  (depth 2)
  u8
  32)
(type 
  connection
  record
  (fingerprint 75cc13f8e2ab406cfa686f3d8808300ca796ceb9)
  (size 60 60)
  (depth 3)
  (fields 
    (field long_addr 0 u64)
    (field fw_version 1 u32)
    (field time 2 u32)
    (field pan_id 3 u16)
    (field short_addr 4 u16)
    (field gateway_addr 5 u16)
    (field connected 6 u8)
    (field pan_seq 7 u8)
    (field radio_index 8 u8)
    (field channel 9 u8)
    (field speed 10 u8)
    (field key_slot 11 u8)
    (field sess_key 12 arr_u8_32)))
(type 
  req_connect
  union
  (fingerprint 8674722d963002f4d2df45fce9d6bcb0b4b2f73c)
  (size 1 61)
  (depth 4)
  t1
  (fields (empty cold 0) (field quick 1 connection)))
(type 
  cmd_connect
  union
  (fingerprint d91f43fd8069309b9595b96306d02e058cad2dfd)
  (size 2 62)
  (depth 5)
  t1
  (fields (field req 0 req_connect) (field res 1 res_connect)))
(type 
  sleep_connection
  union
  (fingerprint 752048ed5ce1746134694b27e0f9a3cb26ba9085)
  (size 1 61)
  (depth 4)
  t1
  (fields 
    (empty not_connected 0)
    (empty keep_awake 1)
    (empty needs_reset 2)
    (field connection 3 connection)))
(type 
  res_sleep
  record
  (fingerprint 2fae84c462d26394ef13b68b9e4de653492551a1)
  (size 2 62)
  (depth 5)
  (fields (field needs_reset 0 bool) (field connection 1 sleep_connection)))
(type 
  cmd_sleep
  union
  (fingerprint e4835413656aa227a34b42dd31faf7fc723d4517)
  (size 1 63)
  (depth 6)
  t1
  (fields (empty req 0) (field res 1 res_sleep)))
(type 
  cmd
  union
  (fingerprint e8bd4ff6c5608928d79b82bbc383b4a57ad38f59)
  (size 2 108)
  (depth 7)
  t1
  (fields 
    (field info 0 cmd_info)
    (field send 1 cmd_send)
    (field connect 2 cmd_connect)
    (field connected 3 cmd_connected)
    (field poll 4 cmd_poll)
    (field sleep 5 cmd_sleep)))
(type 
  txn
  record
  (fingerprint ce4163336f1a1f55cb5b6107b8a93e448d0fd605)
  (size 4 110)
  (depth 8)
  (fields (field seq 0 u16) (field cmd 1 cmd)))
