#include <stdlib.h>
#include "sway/commands.h"
#include "sway/config.h"
#include "sway/lock.h"
#include "util.h"

struct cmd_results *cmd_session_lock_xray(int argc, char **argv) {
	struct cmd_results *error =
		checkarg(argc, "session_lock_xray", EXPECTED_AT_LEAST, 1);
	if (error) {
		return error;
	}

	config->session_lock_xray =
		parse_boolean(argv[0], config->session_lock_xray);

	if (config->session_lock_xray) {
		setenv("SWAYFX_SESSION_LOCK_XRAY", "1", 1);
	} else {
		unsetenv("SWAYFX_SESSION_LOCK_XRAY");
	}

	sway_session_lock_update_background();

	return cmd_results_new(CMD_SUCCESS, NULL);
}
