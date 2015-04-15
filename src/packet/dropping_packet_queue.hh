/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef DROPPING_PACKET_QUEUE_HH
#define DROPPING_PACKET_QUEUE_HH

#include <queue>
#include <cassert>

#include "abstract_packet_queue.hh"

class DroppingPacketQueue : public AbstractPacketQueue
{
private:
    int queue_size_in_bytes_ = 0, queue_size_in_packets_ = 0;

    std::queue<QueuedPacket> internal_queue_ {};

protected:
    const unsigned int packet_limit_;
    const unsigned int byte_limit_;

    unsigned int size_bytes( void ) const;
    unsigned int size_packets( void ) const;

    /* put a packet on the back of the queue */
    void accept( QueuedPacket && p );

    /* are the limits currently met? */
    bool good( void ) const;

public:
    DroppingPacketQueue( const std::string & args );

    virtual void enqueue( QueuedPacket && p ) = 0;

    QueuedPacket dequeue( void ) override;

    bool empty( void ) const override;
};

#endif /* DROPPING_PACKET_QUEUE_HH */ 