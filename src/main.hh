#include "ncurses_ui.hh"
#include "ncurses.h"
#include "file.hh"
#include "string.hh"
#include "buffer.hh"
#include "flags.hh"
#include "client.hh"
#include "option_manager.hh"

using namespace Kakoune;

struct convert_to_client_mode {
  String session;
  String buffer_name;
};

enum class UIType {
  NCurses,
  Json,
  Dummy,
};

int main(int argc, char* argv[]);
int run_server(StringView session,
               StringView init_command,
               bool ignore_kakrc,
               bool daemon,
               UIType ui_type,
               ConstArrayView<StringView> files,
               ByteCoord target_coord);

int run_client(StringView session, StringView init_command, UIType ui_type);

void signal_handler(int signal);

int cli(int argc, char* argv[]);
