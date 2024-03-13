#pragma once

enum failure_state_file{success, wrong_size, invalid_input, function_not_supported,do_not_match,do_not_match_write,do_not_match_append};
enum failure_state_system{success_system,file_already_exist, file_is_null, file_not_open, file_not_exist, file_is_open};
enum failure_command{success_command, command_already_exist, quit, command_not_exist};
enum failure_execute_command{success_execute, fail_to_open_file, fail_to_create_file, file_name_too_long, read_only, already_read_only, already_no_permission, wrong_format};
enum char_num{converter = 48};
enum list_command_loops{none,once,twice};
enum list_command_spacing{maximum_name_length = 20, command_spacing = 2};
