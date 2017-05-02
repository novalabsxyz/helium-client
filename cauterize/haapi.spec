(name "atom_api")
(version "1.0.0")
(fingerprint ed8b5a05c80f822f47e937ba0dc30a2118037901)
(size 1 113)
(depth 8)
(typelength 2)
(lengthtag t1)
(type 
  res_send
  union
  (fingerprint 7bdf1a3149b2ac77ec06a22d267469bf44a9bbd2)
  (size 1 1)
  (depth 1)
  t1
  (fields 
    (empty ok 0)
    (empty err_not_connected 1)
    (empty err_dropped 2)
    (empty err_nack 3)
    (empty err_channel_access 4)))
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
  (fingerprint e5fe6c8dfff18eab7282275179e536547ac4b342)
  (size 1 1)
  (depth 1)
  t1
  (values 
    (value ok 0)
    (value err_not_autonomous 1)
    (value err_fallback_to_slow_connect 2)))
(type 
  radio_frame
  vector
  (fingerprint 2521fbdec6da77f0037c98dfa80b2074a308bb82)
  (size 1 108)
  (depth 2)
  u8
  107
  t1)
(type 
  res_poll
  union
  (fingerprint ef376c4284e59dc13344ff00725d08c45146c7c0)
  (size 1 109)
  (depth 3)
  t1
  (fields (empty none 0) (empty needs_reset 1) (field frame 2 radio_frame)))
(type 
  cmd_send
  union
  (fingerprint 75378e3c1094da6d38e66701fba67feccd8e0ee2)
  (size 2 109)
  (depth 3)
  t1
  (fields (field req 0 radio_frame) (field res 1 res_send)))
(type 
  cmd_poll
  union
  (fingerprint 87ae4091edcc8ecdf973fe3ef8d37f8e601ae0cb)
  (size 1 110)
  (depth 4)
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
  (fingerprint b9c4882ef5c84724551113f056ba01757a70e899)
  (size 56 56)
  (depth 3)
  (fields 
    (field long_addr 0 u64)
    (field pan_id 1 u16)
    (field short_addr 2 u16)
    (field gateway_addr 3 u16)
    (field pan_seq 4 u8)
    (field radio_index 5 u8)
    (field connected 6 u8)
    (field channel 7 u8)
    (field speed 8 u8)
    (field key_slot 9 u8)
    (field sess_key 10 arr_u8_32)
    (field fw_version 11 u32)))
(type 
  quick_connect
  record
  (fingerprint eb9731db19b2eab4274591c3906497b3221d2f0b)
  (size 60 60)
  (depth 4)
  (fields (field time 0 u32) (field connection 1 connection)))
(type 
  req_connect
  union
  (fingerprint be8d983b3db1d9bbd84dcc01a3e28ca45036d0fc)
  (size 1 61)
  (depth 5)
  t1
  (fields (empty cold 0) (field quick 1 quick_connect)))
(type 
  cmd_connect
  union
  (fingerprint 895291932ff8923b16c11713056837bcc932e4ff)
  (size 2 62)
  (depth 6)
  t1
  (fields (field req 0 req_connect) (field res 1 res_connect)))
(type 
  res_sleep
  union
  (fingerprint 205e9021cc3c1b8c868c5ed556de8388096a7f46)
  (size 1 57)
  (depth 4)
  t1
  (fields 
    (empty not_connected 0)
    (empty keep_awake 1)
    (empty needs_reset 2)
    (field connection 3 connection)))
(type 
  cmd_sleep
  union
  (fingerprint 0586ac45e91231948956c3fffe721202791b13f5)
  (size 1 58)
  (depth 5)
  t1
  (fields (empty req 0) (field ress 1 res_sleep)))
(type 
  cmd
  union
  (fingerprint 372ab5c2b64394baf35bc5632f7a7fe26d9cd358)
  (size 2 111)
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
  (fingerprint 7355f8c1f6dc1bf78cc3adcff7398f785364cc1e)
  (size 4 113)
  (depth 8)
  (fields (field seq 0 u16) (field cmd 1 cmd)))
