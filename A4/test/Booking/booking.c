#include "booking.h"

struct Booking mkBooking(int checkin, int checkout){
    struct Booking b;
    b.checkin = checkin;
    b.checkout = checkout;
    return b;
}
