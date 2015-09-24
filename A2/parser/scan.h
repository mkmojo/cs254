/* definitions the scanner shares with the parser */

typedef enum {t_equal, t_nequal, t_lt, t_gt, t_le, t_ge,  // ro 
    t_while, t_if, t_end, t_read, t_write, t_id, t_literal, t_gets, // keywords
    t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof} token; // arithmatic operations

extern char token_image[100];

extern token scan();
