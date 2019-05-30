/* Stack Class
   -----------
   This class uses an array implementation of ADT Stack. It contains
   a char array to store data and an integer value that tracks where
   in the array the top of the stack lies. It contains the following
   methods: isEmpty(), makeNull(), top(), pop(), and push().

   Written by Chris Butterworth
   October 26th, 2014                                             */

import javax.swing.*;

public class Stack
{
	private char[] data;
	private int top;

	public Stack()    // basic constructor
	{
		this.data = new char[20];
		this.top = -1;
	}

	public Stack(int size)    // advanced constructor
	{
		this.data = new char[size];
		this.top = -1;
	}

    /* isEmpty method
       --------------
       Accepts nothing, returns boolean

       This method returns true if stack is empty (top == -1), and
       returns false if the stack is populated (top >= 0).      */

	public boolean isEmpty()
	{
		return (top == -1);
	}

    /* makeNull method
       ---------------
       Accepts and returns nothing

       This method resets the value of top to -1, thus allowing the
       stack to be repopulated.                                  */

	public void makeNull()
	{
		top = -1;
	}

    /* top method
       ----------
       Accepts nothing, returns char

       This method returns the value at the top of the stack. */

	public char top()
	{
		return data[top];
	}

    /* pop method
       ----------
       Accepts and returns nothing

       This method decrements the value of top in order to "pop"
       the current position from the stack.                   */

	public void pop()
	{
		if (isEmpty())
		{
			JOptionPane.showMessageDialog(
                null, "Stack underflow!", "Warning!",
                JOptionPane.INFORMATION_MESSAGE);
		}
		else
		{
			top--;
		}
	}

    /* push method
       -----------
       Accepts char, returns boolean

       This method "pushes" a new value onto the stack by incrementing
       the value of top and inserting the value at that position. If
       the stack is full, an error message is displayed and the method
       returns false.						    					*/

	public boolean push(char input)
	{
		boolean success = false;

		if (top == data.length - 1)    // stack is full
		{
			JOptionPane.showMessageDialog(
                null, "Stack overflow!", "Warning!",
                JOptionPane.INFORMATION_MESSAGE);
		}
		else    // stack has room
		{
			top++;
			data[top] = input;
			success = true;
		}

		return success;
	}
}    // end Stack class
