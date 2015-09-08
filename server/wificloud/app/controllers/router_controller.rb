class RouterController < ApplicationController
	def index
		@routers = Router.all()
	end
	
	def new
		
	end

	def ping_io
		@ios = RouterPingIo.where(mac_address: params[:mac]).order("recv_time DESC")
	end

	def save
		@router = Router.new(router_params)
		@router.save
	end

	private
	def router_params  
		params.require(:router).permit(:mac_address, :room_no, :model)
    end  
end