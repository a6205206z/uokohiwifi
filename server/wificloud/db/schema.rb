# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 1) do

  create_table "commands", force: :cascade do |t|
    t.string   "mac_address", limit: 255, default: "",                    null: false
    t.string   "command",     limit: 255, default: "",                    null: false
    t.datetime "create_time",             default: '2015-09-01 06:12:15', null: false
    t.integer  "status",      limit: 2,   default: 0,                     null: false
  end

  create_table "router_ping_ios", force: :cascade do |t|
    t.string   "mac_address", limit: 255, default: "",                    null: false
    t.datetime "recv_time",               default: '2015-09-01 06:12:15', null: false
  end

  create_table "routers", force: :cascade do |t|
    t.string   "mac_address",         limit: 255, default: "",                    null: false
    t.string   "room_no",             limit: 255, default: "",                    null: false
    t.string   "model",               limit: 255, default: "",                    null: false
    t.datetime "register_time",                   default: '2015-09-01 06:12:15', null: false
    t.datetime "last_recv_ping_time",             default: '2015-09-01 06:12:15', null: false
  end

end
