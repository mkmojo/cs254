#include "comp.h"
#include "Booking/booking.h"

int x = 0;
int y = 1;
int main () {
    struct Booking a = mkBooking(1, 2);
    int x = 1;
    {
        struct Booking c = mkBooking(5, 2);
        int y = x + 1;
        min (x, y);
    }

    {
        struct Booking b = mkBooking(2, 3);
        x = y + 2;
        min (x + 1, y);
    }
    x + y;
    
    return 0;
}

