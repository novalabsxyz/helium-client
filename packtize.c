#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <helium-client.h>

void 
send_message(struct helium_channel * channel,
            const char *            data,
            size_t                  m_size,
            uint16_t *              token,
            uint8_t                 position)
{
    int seg_count = (m_size-position)/HELIUM_MAX_DATA_SIZE;
    
    if(seg_count >= 0 && position < m_size){
        char segment[100];
        for (int i = 1; i<HELIUM_MAX_DATA_SIZE; i++)
        {
            if(position < m_size){
                segment[i] = data[position];
                position++;
            }
        }
        segment[0] = seg_count; //the segments count backwards... 
 
        int status = helium_channel_send(channel, segment, HELIUM_MAX_DATA_SIZE, token);
        if(helium_status_OK == status){
            send_message(channel, data, m_size, token, position);
        }
        else{
            send_message(channel, data, m_size, token, 0);
        }
    }
    else{
        printf("Done sending"); 
    }

}

