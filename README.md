# SecurityStriker: Linux Keylogger Connected with Discord

TypeTracker is an advanced keylogging tool developed in C++ specifically for the Linux operating system. It enables discreet and responsible monitoring of keyboard input, while also providing a secure connection to Discord for seamless reporting and analysis.

## Features

- **Efficient Monitoring:** TypeTracker captures keyboard input with precision, allowing you to gain insights into user typing behavior, interactions, and patterns.

- **Ethical Usage:** Designed with ethical considerations in mind, TypeTracker empowers you to monitor keyboard activities for legitimate purposes such as educational analysis, user experience optimization, and troubleshooting.

- **Secure Discord Connection:** Utilizing the power of Discord webhooks, TypeTracker securely reports captured data to a specified Discord channel, ensuring the privacy and confidentiality of the logged information.

- **Customizable Reporting:** Configure TypeTracker to report captured keystrokes in a structured and readable format, making it easy to analyze and draw meaningful insights.

## Getting Started

### Prerequisites

- Linux operating system
- C++ compiler (g++)
- Discord webhook URL for reporting (Create one in your Discord server's settings)

### Installation

1. Clone this repository:
   ```sh
   git clone https://github.com/your-username/TypeTracker.git
   cd TypeTracker
   ```

2. Build the keylogger
   ```sh
    g++ main.cpp -o main -lX11 -ldpp -lpthread
   ```

3. Distribute at your own risk.

## Ethical Considerations
TypeTracker is intended for responsible and ethical use. Ensure that you have proper authorization before using this tool and adhere to legal regulations and ethical guidelines in your jurisdiction.

## Disclaimer
This tool is provided for educational and ethical purposes only. The authors and contributors are not responsible for any misuse or illegal activities carried out with this software.
