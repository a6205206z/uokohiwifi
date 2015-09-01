class Router < ActiveRecord::Base
	validates_presence_of	:mac_address,  :message => "MAC address can not be empty!"

	validates_presence_of	:room_no,  :message => "Room No can not be empty!"

	validates_presence_of	:model,  :message => "Model can not be empty!"

	def self.online(mac_address)
		router = Router.find_by(mac_address)
		if !router.nil?
			router.last_recv_ping_time = Time.new
			return router.save
		end
	end

	def online
		return (Time.new - last_recv_ping_time) < (5 * 60)
	end
end