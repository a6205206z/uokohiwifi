class CommandController < ApplicationController
	def save
		@command = Command.new(router_params)
		@command.save
	end

	def new
		@mac_addresses = Router.pluck(:mac_address)
	end

	def show
		@commands = Command.where(mac_address: params[:mac]).order("id DESC")
	end

	private
	def router_params  
		params.require(:command).permit(:mac_address, :command)
    end  
end