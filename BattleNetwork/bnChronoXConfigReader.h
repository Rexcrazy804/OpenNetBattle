#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <map>
#include "bnInputEvent.h"
#include "bnFileUtil.h"

/*
Example file contents generated by the MMBN Chrono X Config Tool
---------------------

[Discord]
RPC="1"
[Audio]
Play="1"
[Net]
uPNP="0"
[Video]
Filter="0"
Size="1"
[Keyboard]
Select="8"
Start="13"
R="83"
L="65"
B="88"
A="90"
Left="37"
Down="40"
Right="39"
Up="38"
[Gamepad]
Select="32777"
Start="32778"
R="32774"
L="32773"
B="32769"
A="32770"
Left="32783"
Down="32782"
Right="32784"
Up="32781"
*/

class ChronoXConfigReader {
public:
  enum Gamepad { };

private:
  // Config values
  // Map keys to actions
  std::map<sf::Keyboard::Key, std::string> keyboard;
  std::map<Gamepad, std::string> gamepad;
  bool isAudioEnabled;

  // State flags
  bool isOK;

  // Aux functions
  void Trim(std::string& line) {
    while (line.compare(0, 1, " ") == 0)
      line.erase(line.begin()); // remove leading whitespaces
    while (line.size() > 0 && line.compare(line.size() - 1, 1, " ") == 0)
      line.erase(line.end() - 1); // remove trailing whitespaces
  }

  std::string ValueOf(std::string _key, std::string _line) {
    int keyIndex = (int)_line.find(_key);
    std::string s = _line.substr(keyIndex + _key.size() + 2);
    return s.substr(0, s.find("\""));
  }

  Gamepad GetGamepadCode(int key) {
    unsigned int vendor = sf::Joystick::getIdentification(0).vendorId;
    unsigned int product = sf::Joystick::getIdentification(0).productId;

    // Start and select on rock candy xbox controller do not map correctly
    if (vendor == 3695 && product == 287) {
      if (key == 32777 || key == 32778) {
        key -= 2;
      }
    }

    key -= 32769; // We want base 0 buttons for SFML
    return (Gamepad)key;
  }

  sf::Keyboard::Key GetKeyCodeFromAscii(int ascii) {
    switch (ascii) {
    case 49:
      return sf::Keyboard::Key::Num1;
    case 50:
      return sf::Keyboard::Key::Num2;
    case 51:
      return sf::Keyboard::Key::Num3;
    case 52:
      return sf::Keyboard::Key::Num4;
    case 53:
      return sf::Keyboard::Key::Num5;
    case 54:
      return sf::Keyboard::Key::Num6;
    case 55:
      return sf::Keyboard::Key::Num7;
    case 56:
      return sf::Keyboard::Key::Num8;
    case 57:
      return sf::Keyboard::Key::Num9;
    case 58:
      return sf::Keyboard::Key::Num0;
    case 13:
      return sf::Keyboard::Key::Return;
    case 8: 
      return sf::Keyboard::Key::BackSpace;
    case 32:
      return sf::Keyboard::Key::Space;
    case 37:
      return sf::Keyboard::Key::Left;
    case 40:
      return sf::Keyboard::Key::Down;
    case 39:
      return sf::Keyboard::Key::Right;
    case 38:
      return sf::Keyboard::Key::Up;
    case 46:
      return sf::Keyboard::Key::Delete;
    case 65:
      return sf::Keyboard::Key::A;
    case 66:
      return sf::Keyboard::Key::B;
    case 67:
      return sf::Keyboard::Key::C;
    case 68:
      return sf::Keyboard::Key::D;
    case 69:
      return sf::Keyboard::Key::E;
    case 70:
      return sf::Keyboard::Key::F;
    case 71:
      return sf::Keyboard::Key::G;
    case 72:
      return sf::Keyboard::Key::H;
    case 73:
      return sf::Keyboard::Key::I;
    case 74:
      return sf::Keyboard::Key::J;
    case 75:
      return sf::Keyboard::Key::K;
    case 76:
      return sf::Keyboard::Key::L;
    case 77:
      return sf::Keyboard::Key::M;
    case 78:
      return sf::Keyboard::Key::N;
    case 79:
      return sf::Keyboard::Key::O;
    case 80:
      return sf::Keyboard::Key::P;
    case 81:
      return sf::Keyboard::Key::Q;
    case 82:
      return sf::Keyboard::Key::R;
    case 83:
      return sf::Keyboard::Key::S;
    case 84:
      return sf::Keyboard::Key::T;
    case 85:
      return sf::Keyboard::Key::U;
    case 86:
      return sf::Keyboard::Key::V;
    case 87:
      return sf::Keyboard::Key::W;
    case 88:
      return sf::Keyboard::Key::X;
    case 89:
      return sf::Keyboard::Key::Y;
    case 90:
      return sf::Keyboard::Key::Z;
    case 112:
      return sf::Keyboard::Key::Tilde;
    case 16:
      return sf::Keyboard::Key::Tab;
    case 162:
      return sf::Keyboard::Key::LControl;
    case 164:
      return sf::Keyboard::Key::LAlt;
    case 165:
      return sf::Keyboard::Key::RAlt;
    case 163:
      return sf::Keyboard::Key::RControl;
    case 186:
      return sf::Keyboard::Key::SemiColon;
    case 187:
      return sf::Keyboard::Key::Equal;
    case 188:
      return sf::Keyboard::Key::Comma;
    case 189:
      return sf::Keyboard::Key::Dash;
    case 190:
      return sf::Keyboard::Key::Period;
    case 191:
      return sf::Keyboard::Key::Divide;
    case 219:
      return sf::Keyboard::Key::LBracket;
    case 220:
      return sf::Keyboard::Key::Slash;
    case 221:
      return sf::Keyboard::Key::RBracket;
    case 222:
      return sf::Keyboard::Key::Quote;

    }

    return sf::Keyboard::Key::Unknown;
  }

  // Parsing
  
  const bool Parse(std::string buffer) {
    return ParseDiscord(buffer);
  }

  const bool ParseDiscord(std::string buffer) {
    int endline = 0;

    do {
      endline = (int)buffer.find("\n");
      std::string line = buffer.substr(0, endline);

      Trim(line);

      if (line.find("[Audio]") != std::string::npos) {
        return ParseAudio(buffer);
      }

      // TODO: integrate with discord

      // Read next line...
      buffer = buffer.substr(endline + 1);
    } while (endline > -1);

    return false;
  }

  const bool ParseAudio(std::string buffer) {
    int endline = 0;

    do {
      endline = (int)buffer.find("\n");
      std::string line = buffer.substr(0, endline);

      Trim(line);

      if (line.find("[Net]") != std::string::npos) {
        return ParseNet(buffer);
      }
      else if (line.find("Play") != std::string::npos) {
        std::string enabledStr = ValueOf("Play", line);
        isAudioEnabled = (enabledStr == "1");
      }

      // Read next line...
      buffer = buffer.substr(endline + 1);
    } while (endline > -1);

    return false;
  }

  const bool ParseNet(std::string buffer) {
    int endline = 0;

    do {
      endline = (int)buffer.find("\n");
      std::string line = buffer.substr(0, endline);

      Trim(line);

      if (line.find("[Video]") != std::string::npos) {
        return ParseVideo(buffer);
      }

      // NOTE: networking will not be a feature for some time...

      // Read next line...
      buffer = buffer.substr(endline + 1);
    } while (endline > -1);

    return false;
  }

  const bool ParseVideo(std::string buffer) {
    int endline = 0;

    do {
      endline = (int)buffer.find("\n");
      std::string line = buffer.substr(0, endline);

      Trim(line);

      if (line.find("[Keyboard]") != std::string::npos) {
        return ParseKeyboard(buffer);
      }

      // TODO: handle video settings

      // Read next line...
      buffer = buffer.substr(endline + 1);
    } while (endline > -1);

    return false;
  }

  const bool ParseKeyboard(std::string buffer) {
    int endline = 0;

    do {
      endline = (int)buffer.find("\n");
      std::string line = buffer.substr(0, endline);

      Trim(line);

      if (line.find("[Gamepad]") != std::string::npos) {
        return ParseGamepad(buffer);
      }

      if (line.find("Select") != std::string::npos) {
        std::string value = ValueOf("Select", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "Select"));
      }

      if (line.find("Start") != std::string::npos) {
        std::string value = ValueOf("Start", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "Start"));
      }

      if (line.find("R") != std::string::npos) {
        std::string value = ValueOf("R", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "R"));
      }

      if (line.find("L") != std::string::npos) {
        std::string value = ValueOf("L", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "L"));
      }

      if (line.find("B") != std::string::npos) {
        std::string value = ValueOf("B", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "B"));
      }

      if (line.find("A") != std::string::npos) {
        std::string value = ValueOf("A", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "A"));
      }

      if (line.find("Left") != std::string::npos) {
        std::string value = ValueOf("Left", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "Left"));
      }

      if (line.find("Right") != std::string::npos) {
        std::string value = ValueOf("Right", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "Right"));
      }

      if (line.find("Down") != std::string::npos) {
        std::string value = ValueOf("Down", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "Down"));
      }

      if (line.find("Up") != std::string::npos) {
        std::string value = ValueOf("Up", line);
        keyboard.insert(std::make_pair(GetKeyCodeFromAscii(std::atoi(value.c_str())), "Up"));
      }

      // Read next line...
      buffer = buffer.substr(endline + 1);
    } while (endline > -1);

    return false;
  }

  const bool ParseGamepad(std::string buffer) {
    int endline = 0;

    do {
      endline = (int)buffer.find("\n");
      std::string line = buffer.substr(0, endline);

      Trim(line);

      if (line.find("Select") != std::string::npos) {
        std::string value = ValueOf("Select", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "Select"));
      }

      if (line.find("Start") != std::string::npos) {
        std::string value = ValueOf("Start", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "Start"));
      }

      if (line.find("R") != std::string::npos) {
        std::string value = ValueOf("R", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "R"));
      }

      if (line.find("L") != std::string::npos) {
        std::string value = ValueOf("L", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "L"));
      }

      if (line.find("B") != std::string::npos) {
        std::string value = ValueOf("B", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "B"));
      }

      if (line.find("A") != std::string::npos) {
        std::string value = ValueOf("A", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "A"));
      }

      if (line.find("Left") != std::string::npos) {
        std::string value = ValueOf("Left", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "Left"));
      }

      if (line.find("Right") != std::string::npos) {
        std::string value = ValueOf("Right", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "Right"));
      }

      if (line.find("Down") != std::string::npos) {
        std::string value = ValueOf("Down", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "Down"));
      }

      if (line.find("Up") != std::string::npos) {
        std::string value = ValueOf("Up", line);
        gamepad.insert(std::make_pair(GetGamepadCode(std::atoi(value.c_str())), "Up"));
      }

      // Read next line...
      buffer = buffer.substr(endline + 1);
    } while (endline > -1);

    // We've come to the end of the config file with all expected headers
    return true;
  }

public:

  ChronoXConfigReader(std::string filepath) {
    isOK = Parse(FileUtil::Read(filepath));
  }

  const bool IsOK() { return isOK; }

  const bool IsAudioEnabled() { return isAudioEnabled;  }

  const std::string GetPairedAction(sf::Keyboard::Key event) {
    std::map<sf::Keyboard::Key, std::string>::iterator iter = keyboard.find(event);

    if (iter != keyboard.end()) {
      return iter->second;
    }

    return "";
  }

  const std::string GetPairedAction(Gamepad event) {
    std::map<Gamepad, std::string>::iterator iter = gamepad.find(event);

    if (iter != gamepad.end()) {
      return iter->second;
    }

    return "";
  }

  ~ChronoXConfigReader() { ; }
};