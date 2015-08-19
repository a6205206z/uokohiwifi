#!/usr/bin/lua

local http = require("socket.http")
local ltn12 = require("ltn12")

local UOKO_AD_SERVICE_URL = "http://www.uoko.com/aboutus/contact/"



function http.get(u)
   local t = {}
   local r, c, h = http.request{
      url = u,
      sink = ltn12.sink.table(t)}
   return r, c, h, table.concat(t)
end

function download_ad_page()
	r,c,h,body = http.get(UOKO_AD_SERVICE_URL)
	if c ~= 200 then
	    return
	end
	print(body)
end



if arg[1] == "update" then
	if arg[2] == "ad" then
		download_ad_page()
	end	
end