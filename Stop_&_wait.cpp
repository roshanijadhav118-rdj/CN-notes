#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// ----------------------------------------------------
// 10-second timer
// ----------------------------------------------------
void startTimer()
{
    cout << "\nTimer started for 3 seconds...\n";

    for (int i = 3; i >= 1; i--)
    {
        cout << "\rTime remaining: " << i << " seconds"
             << flush;

        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "\nTIMEOUT!\n";
}

// ----------------------------------------------------
// Main program
// ----------------------------------------------------
int main()
{
    int totalFrames;

    cout << "============================================\n";
    cout << "          STOP AND WAIT ARQ\n";
    cout << "============================================\n";

    cout << "Enter number of frames: ";
    cin >> totalFrames;

    if (totalFrames <= 0)
    {
        cout << "Invalid number of frames.\n";
        return 0;
    }

    // Initialize random number generator
    srand(time(0));

    // Alternating sequence number
    int sequenceNumber = 0;

    // Process every frame
    for (int frame = 0; frame < totalFrames; frame++)
    {
        bool acknowledged = false;
        int attempt = 1;

        while (!acknowledged)
        {
            cout << "\n--------------------------------------------\n";
            cout << "Frame Number     : " << frame << endl;
            cout << "Sequence Number  : " << sequenceNumber << endl;
            cout << "Transmission No. : " << attempt << endl;
            cout << "--------------------------------------------\n";

            cout << "\nSender -> Receiver : Sending Frame "
                 << frame << "...\n";

            // ------------------------------------------------
            // Randomly select channel condition
            // 0 = Successful
            // 1 = Frame lost
            // 2 = ACK lost
            // ------------------------------------------------
            int condition = rand() % 3;

            // =================================================
            // CONDITION 1: Frame and ACK successfully received
            // =================================================
            if (condition == 0)
            {
                cout << "Receiver : Frame " << frame
                     << " received successfully.\n";

                cout << "Receiver -> Sender : ACK "
                     << sequenceNumber << " sent.\n";

                cout << "Sender : ACK " << sequenceNumber
                     << " received successfully.\n";

                cout << "\nFrame " << frame
                     << " completed successfully.\n";

                acknowledged = true;
            }

            // =================================================
            // CONDITION 2: FRAME LOST
            // =================================================
            else if (condition == 1)
            {
                cout << "Receiver : Frame " << frame
                     << " is LOST!\n";

                cout << "Sender : ACK not received.\n";

                startTimer();

                cout << "\nSender : Timeout occurred.\n";
                cout << "Sender : Retransmitting Frame "
                     << frame << "...\n";

                attempt++;
            }

            // =================================================
            // CONDITION 3: ACK LOST
            // =================================================
            else
            {
                cout << "Receiver : Frame " << frame
                     << " received successfully.\n";

                cout << "Receiver -> Sender : ACK "
                     << sequenceNumber << " sent.\n";

                cout << "Channel : ACK " << sequenceNumber
                     << " is LOST!\n";

                cout << "Sender : ACK not received.\n";

                startTimer();

                cout << "\nSender : Timeout occurred.\n";
                cout << "Sender : Retransmitting Frame "
                     << frame << "...\n";

                attempt++;
            }
        }

        // ------------------------------------------------
        // Change sequence number after successful ACK
        // 0 -> 1 -> 0 -> 1 ...
        // ------------------------------------------------
        sequenceNumber = 1 - sequenceNumber;
    }

    cout << "\n============================================\n";
    cout << "All " << totalFrames
         << " frames transmitted successfully.\n";
    cout << "STOP AND WAIT ARQ COMPLETED.\n";
    cout << "============================================\n";

    return 0;
}
