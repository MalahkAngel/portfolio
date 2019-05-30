/* Bracket class
   -------------

   This program utilizes an array implementation of the ADT Stack
   in order to determine if user provided expressions are valid.
   Expressions are evaluated as valid if all brackets--(), [], {}--match.
   Matches are determined by the match method, detailed below.

   Written by Chris Butterworth
   October 28th, 2014							                       */

import javax.swing.*;

public class Bracket
{
	public static void main(String [] args)
	{
		Stack stack = new Stack();
		String input;
		boolean done = false;

		while (!done)
		{
			stack.makeNull();    // initialize stack
			input = JOptionPane.showInputDialog(
				"Please enter an expression. Cancel to quit.");

			if (input == null)
			{
				done = true;
			}
			else
			{
				match(stack, input);    // check for matched brackets
			}
		}
	}    // end main

	/* match method
	   ------------

	   Accepts Stack object & String
	   Returns nothing

	   This method takes the initialized stack and user input, then
	   parses opening brackets from it, pushing them onto the stack.
	   From the first bracket on, it compares the top value of the
	   stack against the user input, popping values as matching
	   brackets are found. If all brackets match, the stack will be
	   empty resulting in a valid expression. Otherwise, the stack
	   will be populated resulting in an invalid expression.      */

	public static void match(Stack stack, String input)
	{
		char next;

		for (int i = 0; i < input.length(); i++)
		{
			next = input.charAt(i);

			// check for brackets to push (including closing brackets at start)
			if ((next == '(' || next == '['|| next == '{') ||
				(next == ')' || next == ']'|| next == '}') && stack.isEmpty())
			{
				if(!stack.push(next))
				{
					i = input.length();
				}
			}
			// check top of stack against next entry
			else if ((next == ')' && stack.top() == '(') ||
				(next == ']' && stack.top() == '[') ||
				(next == '}' && stack.top() == '{'))
			{
				stack.pop();
			}
		}    // end for

		if (stack.isEmpty())    // all brackets match
		{
			JOptionPane.showMessageDialog(
				null, "The expression is valid.", "Success",
				JOptionPane.INFORMATION_MESSAGE);
		}
		else    // invalid expression
		{
			JOptionPane.showMessageDialog(
				null, "The expression is invalid.", "Failure",
				JOptionPane.INFORMATION_MESSAGE);
		}
	}    // end match method
}    // end Bracket class
