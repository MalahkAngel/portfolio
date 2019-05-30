/* Oddjob class

   This program makes use of a Queue ADT (either Circular Buffer of
   Pointer implementation) in order to create a queue of jobs to be
   done. The program first initializes the queue and passes it to
   a method to process user input. From there, various tasks
   depending on user input are performed to manipulate the queue.
   The user may choose to add a job to the queue, display and remove
   a job, clear all jobs, or quit.

   Written by Chris Butterworth
   November 12th, 2014											  */

import javax.swing.*;

public class Oddjob
{
	public static void main(String [] args)
	{
		Queue queue = new Queue();    // initialize queue
		mainMenu(queue);    // process user input
		System.exit(0);
	}

	/* mainMenu method

	   Accepts Queue object, returns nothing

	   This method processes user input in order to manipulate
	   the queue. Depending on input, the user may add a job to
	   the queue, display and remove a job from the queue,
	   clear all jobs from the queue, or quit.				 */

	public static void mainMenu(Queue queue)
	{
		String select, message;

		message = "Please select one of the following:\n\t" +
			"A to add a job\n\t" + "G to get the next job\n\t" +
			"C to clear all jobs\n\t" + "Q to quit";

		select = JOptionPane.showInputDialog(message);

		while (!(select.equalsIgnoreCase("q")))    // user has not quit
		{
			if (select.equalsIgnoreCase("a"))    // add to the queue
			{
				add(queue);
			}
			else if (select.equalsIgnoreCase("g"))    // remove from queue
			{
				get(queue);
			}
			else if (select.equalsIgnoreCase("c"))    // clear all jobs
			{
				clear(queue);
			}

			select = JOptionPane.showInputDialog(message);
		}    // end while
	}    // end mainMenu method

	/* add method

	   accepts Queue object, returns nothing

	   This method allows the user to add a job to the queue. Input is
	   given and processed through the Queue ADT's enqueue method. If
	   the insertion fails, an error message displays to notify the
	   user of a queue overflow.									*/

	public static void add(Queue queue)
	{
		String input = JOptionPane.showInputDialog("Please enter a job.");

		if (!(queue.enqueue(input)))    // insertion has failed
		{
			JOptionPane.showMessageDialog (null, "Queue Overflow!",
				"Error!", JOptionPane.ERROR_MESSAGE);
		}
	}

	/* get method

	   Accepts Queue object, returns nothing

	   This method checks to see if the queue is empty. If it is, an
	   error message is displayed to notify the user of a queue
	   underflow. If it is not empty, the frontmost value of the queue
	   is displayed and dequeued.									*/

	public static void get(Queue queue)
	{
		String job;

		if (queue.isEmpty())    // check if queue is empty
		{
			JOptionPane.showMessageDialog(null, "Queue Underflow!",
				"Error!", JOptionPane.ERROR_MESSAGE);
		}
		else    // queue is populated
		{
			job = queue.front();
			JOptionPane.showMessageDialog(null, job, "Message",
				JOptionPane.INFORMATION_MESSAGE);
			queue.dequeue();
		}
	}

	/* clear method

	   Accepts Queue object, returns nothing

	   This method reinitializes the queue through the Queue ADT's
	   makeNull method. The method first makes sure the user wants
	   to remove all jobs. If "Yes" is clicked, the queue's indices
	   are set back to their initial values and the user is notified
	   of the change. If "No" is clicked, the method exits back to
	   the main menu.											  */

	public static void clear(Queue queue)
	{
		int select = JOptionPane.showConfirmDialog(null,
			"Are you sure you want to clear the queue?", "Warning!",
			JOptionPane.YES_NO_OPTION);

		if (select == JOptionPane.YES_OPTION)    // user clicks "yes"
		{
			queue.makeNull();
			JOptionPane.showMessageDialog(null, "Queue has been cleared.",
				"Message", JOptionPane.INFORMATION_MESSAGE);
		}
	}
}    // end Oddjob class
