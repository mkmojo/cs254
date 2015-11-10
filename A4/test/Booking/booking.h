#ifndef BOOKING_H
#define BOOKING_H
struct Booking
{
   int checkin;
   int checkout;
};

struct Booking mkBooking(int, int);
#endif
