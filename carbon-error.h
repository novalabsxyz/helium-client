#ifndef CARBON_ERROR_H
#define CARBON_ERROR_H

enum carbon_status
{
    carbon_status_OK,
    carbon_status_ERR_COMMUNICATION,
    carbon_status_ERR_NOT_CONNECTED,
    carbon_status_ERR_TIMEOUT,
    carbon_status_ERR_DROPPED,
    carbon_status_ERR_KEEP_AWAKE,
    carbon_status_ERR_FAILED,
    carbon_status_ERR_NOT_FOUND,
};

enum carbon_info_status
{
    carbon_info_OK                = carbon_status_OK,
    carbon_info_ERR_COMMUNICATION = carbon_status_ERR_COMMUNICATION,
};

enum carbon_connected_status
{
    carbon_connected_CONNECTED         = carbon_status_OK,
    carbon_connected_NOT_CONNECTED     = carbon_status_ERR_NOT_CONNECTED,
    carbon_connected_ERR_COMMUNICATION = carbon_status_ERR_COMMUNICATION,
};

enum carbon_connect_status
{
    carbon_connect_CONNECTED           = carbon_status_OK,
    carbon_connect_NOT_CONNECTED       = carbon_status_ERR_NOT_CONNECTED,
    carbon_connect_ERR_CONNECT_TIMEOUT = carbon_status_ERR_TIMEOUT,
    carbon_connect_ERR_COMMUNICATION   = carbon_status_ERR_COMMUNICATION,
};

enum carbon_sleep_status
{
    carbon_sleep_OK                = carbon_status_OK,
    carbon_sleep_ERR_NOT_CONNECTED = carbon_status_ERR_NOT_CONNECTED,
    carbon_sleep_ERR_KEEP_AWAKE    = carbon_status_ERR_KEEP_AWAKE,
    carbon_sleep_ERR_COMMUNICATION = carbon_status_ERR_COMMUNICATION,
};

enum carbon_channel_create_status
{
    carbon_channel_create_OK                = carbon_status_OK,
    carbon_channel_create_ERR_FAILED        = carbon_status_ERR_FAILED,
    carbon_channel_create_ERR_NOT_CONNECTED = carbon_status_ERR_NOT_CONNECTED,
    carbon_channel_create_ERR_DROPPED       = carbon_status_ERR_DROPPED,
    carbon_channel_create_ERR_TIMEOUT       = carbon_status_ERR_TIMEOUT,
    carbon_channel_create_ERR_COMMUNICATION = carbon_status_ERR_COMMUNICATION,
};

enum carbon_channel_send_status
{
    carbon_channel_send_OK                = carbon_status_OK,
    carbon_channel_send_ERR_NOT_FOUND     = carbon_status_ERR_NOT_FOUND,
    carbon_channel_send_ERR_NOT_CONNECTED = carbon_status_ERR_NOT_CONNECTED,
    carbon_channel_send_ERR_DROPPED       = carbon_status_ERR_DROPPED,
    carbon_channel_send_ERR_TIMEOUT       = carbon_status_ERR_TIMEOUT,
    carbon_channel_send_ERR_COMMUNICATION = carbon_status_ERR_COMMUNICATION,
};



#endif
