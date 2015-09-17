with Ada.Text_IO; 
use Ada.Text_IO;
with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;

procedure prog is
   arraySize : Integer := 0;
   type myArray is array(Integer range <>) of Integer;
begin
   -- Get Array size from user.
   put_line("How big would you like the array?");
   get(arraySize);

   declare
      theArray : myArray(0..arraySize);
   begin
      for I in 0..arraySize Loop
         theArray(I) := I;
      end Loop;
   end;
end prog;
