class CommandController < ApplicationController
	def create
		@command = Command.new(router_params)
		@command.save
	end

	def new
		@mac = params[:mac]
		@commands = Command.where(mac_address: params[:mac]).order("id DESC")
	end

	def show
		@commands = Command.where(mac_address: params[:mac]).order("id DESC")
	end

	private
	def router_params  
		params.require(:command).permit(:mac_address, :command)
    end  
end