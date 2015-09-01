class Command < ActiveRecord::Base
	validates_presence_of	:mac_address,  :message => "MAC address can not be empty!"

	validates_presence_of	:command,  :message => "Command No can not be empty!"

	def self.exec_command(mac_address)
		cmd_str = "NOTHING"
		cmd = Command.find_by(mac_address: mac_address,status: 0)
		if !cmd.nil?
			cmd_str = cmd.command
			cmd.status = 1
			cmd.save
		end
		return cmd_str
	end
end