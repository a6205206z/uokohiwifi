class Setup < ActiveRecord::Migration
	def self.up
		create_table :routers do |t|
			t.column :mac_address, :string, :default => "", :null => false, :unique => true
			t.column :room_no, :string, :default => "", :null =>false
			t.column :model, :string, :default => "", :null => false
			t.column :register_time, :datetime, :default => Time.new, :null => false
			t.column :last_recv_ping_time, :datetime, :default => Time.new, :null => false
		end

		create_table :router_ping_ios do |t|
			t.column :mac_address, :string, :default => "", :null => false
			t.column :recv_time,  :datetime, :default => Time.new, :null => false
		end

		create_table :commands do |t|
			t.column :mac_address, :string, :default => "", :null => false
			t.column :command, :string, :default => "", :null => false
			t.column :create_time, :datetime, :default => Time.new, :null => false
			t.column :status, :integer, :limit => 2, :default => 0, :null => false
		end
	end

	def self.down
		drop_table :routers
		drop_table :router_ping_ios
		drop_table :commands
	end
end