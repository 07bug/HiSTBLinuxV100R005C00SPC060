Purpose: to demonstrate how to get the key of infrared remotes
Command: sample_ir [-m 0|1] [-u 0|1] [-U num] [-r 0|1] [-R num] [-T readtimeout] [-E 0|1] [-g protocolname] [-l] [-s protocolname -e 0|1] [-h]
Parameter:
				 -m:sets whether key values or raw levels are obtained. -m 0 indicates that key values are obtained, 
				    and -m 1 indicates that raw levels are obtained. Key values are obtained by default.
				 �Cu:sets whether up events are reported. �Cu 0 indicates that up events are not reported,
						and �Cu 1 indicates that up events are reported. Up events are reported by default.
				 �CU:sets the delay for reporting up events. An up event is reported if no repeated key
						value is received within a specific period after a key is pressed. The unit is ms. The value
						cannot be a negative one. The default value is 300 ms. This parameter currently cannot be set by users.
				 �Cr:sets whether repeated keys are reported. �Cr 0 indicates that repeated keys are not
						reported, and �Cr 1 indicates that repeated keys are reported. Repeated keys are reported
						by default. If a key on the remote control is quickly and repeatedly pressed, the driver
						reports repeated keys. If reporting of repeated keys is disabled, the driver does not report repeated keys but generates an alarm.
				 �CR:sets the interval for reporting repeated keys. The unit is ms. The default value is 200ms. The value cannot be a negative one.
  			 �CT:sets the read timeout interval. The driver does not time out by default and waits until
						an infrared key is pressed. The unit is ms. The value cannot be a negative one.
    		 �CE:sets whether the infrared module is enabled. �CE 0 indicates that the infrared module
						is disabled and the chip does not receive any infrared signals. �CE 1 indicates that the
						infrared module is enabled, the chip can receive infrared signals, the driver parses and reports key values. The infrared module is enabled by default.
				 �Cg:used to check whether a protocol is enabled. The �Cg parameter is followed by a
						protocol name. The protocol name can be obtained by using the �Cl parameter. If the
						protocol name contains a space, use quotation marks to enclose the protocol name. For
						example, �Cg "rc6 32bit data". If the protocol name does not contain a space, do not use quotation marks.
				 �Cl:used to obtain the names of all protocols supported by the infrared driver.
				 �Cs:The �Cs parameter is valid only when it is used with the �Ce parameter. The �Cs
						parameter is used to set whether a protocol supported by the infrared driver is enabled. If
						a protocol is disabled, the driver discards and does not parse infrared signals complying
						with the protocol when receiving them. The �Cs parameter is followed by a protocol name. If the protocol name contains a space,
						use quotation marks to enclose the protocol name. Example: �Cs "rc6 32bit data"
				 �Ce:The �Ce parameter is valid only when it is used with the �Cs parameter. The �Ce
						parameter is followed by the value 0 or 1. 0 indicates that a protocol is disabled, and 1
						indicates that a protocol is enabled. For details, see the �Cs parameter.
				 �Ch:used to display help information and exit.
				 
Notice: The parameters are case-sensitive.