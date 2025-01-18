# GitHub User Activity

This project is my solution to the [GitHub User Activity](https://roadmap.sh/projects/github-user-activity) challenge by Roadmap.sh.
It demonstrates how to use C++ to build a simple and efficient command-line tool to fetch and display recent GitHub user activity.

## 🧑‍💻 What did I learn from this project?

 - **Cross-platform compatibility:** I developed and tested the project to ensure it runs smoothly on both Windows and Unix-based systems (Linux/MacOS).
 - **API Communication:** I implemented requests to the GitHub API over HTTPS, exploring how to consume RESTful APIs and parsing JSON responses directly in C++.
 - **Use of standard libraries:**
   - The project relies heavily on C++ standard libraries, minimizing external dependencies.
   - The only external library used is OpenSSL, to handle secure HTTPS communication.

## ⚙️ Technologies and Tools used

- **Language:** C++
- **CLI Structure:** Input/output handling
- **API Client:** Request user activity from Github API
- **HTTP Client:** Standard system library
- **HTTPS Connection:** OpenSSL
- **Development environment:** Compatible with Windows and Unix-based systems.

## 🛠️ How to Run the Project

### Prerequisites

- For compile:
  - **Windows**: MSVC (Visual Studio Developer Command Prompt)
  - **Linux**: GCC (GNU Compiler Collection)
  - [OpenSSL library](https://openssl-library.org/source/) installed

- For run:
  - Internet connection

### Steps to Execute

1. Clone the repository:
   ```bash
   git clone https://github.com/jmsmarcelo/github-user-activity-cpp.git
   cd github-user-activity-cpp
   ```
2. Compile the project:
   ```bash
   mkdir build
   cd build

   # Linux:
   g++ -std=c++17 -o github-activity ../src/*.cpp -lssl -lcrypto -lpthread

   # Windows (Visual Studio Developer Command Prompt):
   cl /std:c++17 /EHsc /Fe:github-activity.exe ..\src\*.cpp /I"path\to\OpenSSL\include" ws2_32.lib /link /LIBPATH:"path\to\OpenSSL\lib" libssl.lib libcrypto.lib
   ```
3. Run the application:
   ```bash
   # Linux:
   ./github-activity <username>

   # Windows:
   .\github-activity <username>
   ```

## 📌 Usage
```bash
# Example:
github-activity kamranahmedse
# output:
# - Pushed 2 commits to kamranahmedse/developer-roadmap
# - Created a comment on an issue in kamranahmedse/developer-roadmap
# - Closed a issue in kamranahmedse/developer-roadmap
```

## 📦 Project Structure
```bash
github-user-activity-cpp/
├─ include/
│  ├─ api_cli.hpp             # CLI API declarations to handle user commands and integrate with the service.
│  ├─ ApiService.hpp          # Core logic for managing GitHub user activity data.
│  ├─ ApiClient.hpp           # Interface for interacting with the GitHub API to fetch user activity.
│  ├─ HttpClient.hpp          # Abstraction for HTTP communications, handling requests and responses.
│  └─ HttpException.hpp       # Custom exceptions for handling HTTP-related errors gracefully.
└─ src/
   ├─ main.cpp                # Application entry point, initializes and runs the CLI.
   ├─ api_cli.cpp             # Implementation of CLI commands, interfacing with the service layer.
   ├─ ApiService.cpp          # Implementation of logic for processing and managing GitHub user activity.
   ├─ ApiClient.cpp           # Implementation of interactions with the GitHub API.
   ├─ HttpClient.cpp          # HTTP client logic for sending requests and parsing responses.
   └─ HttpException.cpp       # Implementation of HTTP-specific exception handling.
```
## 🖼️ Screenshots
![Screenshot Linux](https://github.com/user-attachments/assets/3d9fea3a-5ffd-452c-b68a-09aa43be53ab)

## 📖 How to Contribute

Contributions are welcome!

To contribute:
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b my-new-feature
   ```
3. Commit your changes:
   ```bash
   git commit -m "add new feature"
   ```
4. Push to the branch:
   ```bash
   git push origin my-new-feature
   ```
5. Open a Pull Request.

## 📜 License
This project is licensed under the **MIT License**. See the [LICENSE](https://github.com/jmsmarcelo/github-user-activity-cpp/blob/main/LICENSE) file for details.

## 🙋‍♂️ Author
Created by [Jose Marcelo](https://jmsmarcelo.github.io). Feel free to get in touch or explore more of my projects!
