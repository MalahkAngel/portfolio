/* Queue class

   This class implements the Queue ADT through a circular buffer.
   It contains 2 constructors as well as five operation methods:
   front(), enqueue(), dequeue(), isEmpty(), and makeNull().

   Written by Chris Butterworth
   November 12th, 2014                                         */

public class Queue
{
    private String[] data;
    private int head;
    private int tail;

    public Queue()    // basic constructor
    {
        this.data = new String[10];
        this.head = -1;
        this.tail = head;
    }

    public Queue(int size)    // custom constructor
    {
        this.data = new String[size];
        this.head = -1;
        this.tail = head;
    }

    /* front method

       Accepts nothing, returns String

       This method simply returns the data held within
       the head of the queue.                       */

    public String front()
    {
        return this.data[head];
    }

    /* enqueue method

       Accepts String, returns boolean

       This method first checks to see if the queue is empty.
       If it is, the first entry is placed at the beginning of
       the queue. If the queue is not empty, the tail index
       is incremented and subjected to various checks to ensure
       that the queue is not full as well as wrapping the queue
       if necessary. If the queue passes all checks, the value
       is inserted at the current tail position. Upon any
       successful insertion, the method returns true. If the
       insertion fails, the method returns false.            */

    public boolean enqueue(String input)
    {
        boolean done = false;

        if (isEmpty())    // queue is empty
        {
            head++;
            tail++;
            data[head] = input;
            done = true;
        }
        else    // queue is populated
        {
            tail++;

            if (tail == data.length)    // tail needs to wrap
            {
                tail = 0;

                if (tail != head)    // queue has room
                {
                    data[tail] = input;
                    done = true;
                }
            }
            else if (tail != head)    // queue has room
            {
                data[tail] = input;
                done = true;
            }
        }

        return done;
    }   // end enqueue method

    /* dequeue method

       Accepts and returns nothing

       This method increments the head index in order to remove
       a value. After incrementing, several checks are performed
       to ensure that the queue is not empty and to allow the
       head index to wrap if it reaches the length of the array.
       If the head index reaches the tail, the queue is empty and
       is reinitialized.                                       */

    public void dequeue()
    {
        head++;

        if (head == data.length)    // head needs to wrap
        {
            head = 0;

            if (head == tail)    // queue is empty
            {
                makeNull();
            }
        }
        else if (head == tail)    // queue is empty
        {
            makeNull();
        }
    }   // end dequeue method

    /* isEmpty method

       Accepts nothing, returns boolean

       This method checks whether or not the queue is empty by
       checking the head index against its initialized value.
       If true, the queue is empty. If false, the queue is
       populated.                                           */

    public boolean isEmpty()
    {
        return (head == -1);
    }

    /* makeNull method

       Accepts and returns nothing

       This method reinitializes the queue by setting the head
       and tail indices to -1, allowing the queue to start over
       and be repopulated.                                   */

    public void makeNull()
    {
        head = -1;
        tail = -1;
    }
}   // end Queue class
