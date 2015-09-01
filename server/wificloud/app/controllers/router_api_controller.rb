class RouterApiController < ApiController
	def ping
		@msg = ""
		if request.headers["User-Agent"] and request.headers["User-Agent"].include?"UokoHiwifi"

			if params[:requesttype] == "heartbeat"
				if params[:mac].nil?
					@msg = "ERROR:mac address is null"
				else
					Router.online(mac_address: params[:mac])
					io = RouterPingIo.new :mac_address => params[:mac],
										  :recv_time => Time.new

					io.save

					@msg = Command.exec_command(params[:mac])
				end
			else
				@msg = "ERROR:invalid request"
			end
		else
			@msg = "ERROR:clinet is not UokoHiwifi"
		end
	end
	skip_before_filter :verify_authenticity_token  
end