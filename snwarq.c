#include <stdio.h>
// for sleep()

void stopandwait(int n, int tt, int tp)
{
    int time = 0;
    printf("t%d Waiting\n", time);
    for (int i = 1; i <= n; i++)
    {
        // Wait for propagation time
        if (i % 3 == 0)
        {
            time += tt;
            printf("t%d Timeout for packet %d\n", time, i);
            // Simulate timeout
            time += 3 * (2 * tp);
            printf("t%d Packet %d retransmitted\n", time, i);
            printf("t%d Packet %d received\n", time + tp, i);

            time += tp; // Increment time by propagation time
            time += tt;
            printf("t%d Ack for packet %d received\n", time + tp, i);
            time += tp; // Increment time by transmission time
        }
        else
        {
            printf("t%d Packet %d sent\n", time + tt, i);
            time += tt; // Increment time by 1 ms for sending packet

            printf("t%d Packet %d received\n", time + tp, i);
            time += tp; // Increment time by propagation time
            time += tt; // Increment time by transmission time

            printf("t%d Ack for packet %d received\n", time + tp, i);
            time += tp; // Increment time by transmission time

            // Check if the packet is lost (every 3rd packet)
        }
    }
}

int main()
{
    int total_pack = 15;
    int tt;

    printf("Enter transmission time (in ms): ");
    scanf("%d", &tt);

    int tp;
    printf("Enter propagation time (in ms): ");
    scanf("%d", &tp);

    stopandwait(total_pack, tt, tp);

    return 0;
}