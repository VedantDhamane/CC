
#include <math.h>
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int tt, tp, size;
int windowIdx = 0, time = 0;

void sendWindow() {
    int packets = windowIdx + size;
    while (windowIdx < packets) {
        time += tt;
        printf("Sending packet %d at time %d ms.\n", windowIdx++ + 1, time);
    }
}

int main(void) {
    printf("Enter the transmission time: ");
    scanf("%d", &tt);

    printf("Enter the propogation time: ");
    scanf("%d", &tp);

    printf("Enter the window size: ");
    scanf("%d", &size);

    // Ask user for total packets to send.
    int totalPackets = 10;

    sendWindow();
    time += tp - (size - 1) * tt;

    fflush(stdin);
    do {
        char ack;
        printf("Do you want to acknowledge packet %d (y/n): ", windowIdx - size + 1);
        scanf(" %c", &ack);

        if (ack == 'y') {
            printf("Acknowledgement for packet %d receieved at %d ms.\n", windowIdx - size + 1,
                   time);

            time += tt;
            printf("Sending packet %d at %d ms.\n", windowIdx++ + 1, time);
        } else {
            printf("Not received acknowledgement for packet %d, waited till %d ms.\n",
                   windowIdx - size + 1, time);

            windowIdx -= size;
            sendWindow();
        }
    } while (windowIdx < totalPackets);
}
