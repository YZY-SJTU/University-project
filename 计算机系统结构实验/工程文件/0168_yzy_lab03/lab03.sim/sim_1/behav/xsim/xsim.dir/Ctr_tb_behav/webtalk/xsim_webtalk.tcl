webtalk_init -webtalk_dir E:/archlabs/lab03/lab03.sim/sim_1/behav/xsim/xsim.dir/Ctr_tb_behav/webtalk/
webtalk_register_client -client project
webtalk_add_data -client project -key date_generated -value "Wed Mar 31 12:05:11 2021" -context "software_version_and_target_device"
webtalk_add_data -client project -key product_version -value "XSIM v2018.3 (64-bit)" -context "software_version_and_target_device"
webtalk_add_data -client project -key build_version -value "2405991" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_platform -value "WIN64" -context "software_version_and_target_device"
webtalk_add_data -client project -key registration_id -value "211183177_1777516887_210631861_667" -context "software_version_and_target_device"
webtalk_add_data -client project -key tool_flow -value "xsim_vivado" -context "software_version_and_target_device"
webtalk_add_data -client project -key beta -value "FALSE" -context "software_version_and_target_device"
webtalk_add_data -client project -key route_design -value "FALSE" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_family -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_device -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_package -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_speed -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key random_id -value "4ff72608-0a73-492f-bbb6-2745dc7024d7" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_id -value "6977b2b498a347998cb4c9f2bbe62cf5" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_iteration -value "14" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_name -value "Microsoft Windows 8 or later , 64-bit" -context "user_environment"
webtalk_add_data -client project -key os_release -value "major release  (build 9200)" -context "user_environment"
webtalk_add_data -client project -key cpu_name -value "Intel(R) Xeon(R) CPU E5-1620 v3 @ 3.50GHz" -context "user_environment"
webtalk_add_data -client project -key cpu_speed -value "3492 MHz" -context "user_environment"
webtalk_add_data -client project -key total_processors -value "1" -context "user_environment"
webtalk_add_data -client project -key system_ram -value "17.000 GB" -context "user_environment"
webtalk_register_client -client xsim
webtalk_add_data -client xsim -key Command -value "xsim" -context "xsim\\command_line_options"
webtalk_add_data -client xsim -key trace_waveform -value "true" -context "xsim\\usage"
webtalk_add_data -client xsim -key runtime -value "1 us" -context "xsim\\usage"
webtalk_add_data -client xsim -key iteration -value "0" -context "xsim\\usage"
webtalk_add_data -client xsim -key Simulation_Time -value "0.01_sec" -context "xsim\\usage"
webtalk_add_data -client xsim -key Simulation_Memory -value "6404_KB" -context "xsim\\usage"
webtalk_transmit -clientid 2495159925 -regid "211183177_1777516887_210631861_667" -xml E:/archlabs/lab03/lab03.sim/sim_1/behav/xsim/xsim.dir/Ctr_tb_behav/webtalk/usage_statistics_ext_xsim.xml -html E:/archlabs/lab03/lab03.sim/sim_1/behav/xsim/xsim.dir/Ctr_tb_behav/webtalk/usage_statistics_ext_xsim.html -wdm E:/archlabs/lab03/lab03.sim/sim_1/behav/xsim/xsim.dir/Ctr_tb_behav/webtalk/usage_statistics_ext_xsim.wdm -intro "<H3>XSIM Usage Report</H3><BR>"
webtalk_terminate
