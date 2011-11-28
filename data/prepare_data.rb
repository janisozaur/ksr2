#!/usr/bin/ruby

require 'rubygems'
require 'hpricot'
require 'open-uri'

$base_uri = "http://www.as.up.krakow.pl/weather/text/"

def parse_file filename
	file = open($base_uri + filename)
	data = []
	file.each { |line|
		if (/(?<year>[[:digit:]]{2})-(?<month>[[:digit:]]{2})-(?<day>[[:digit:]]{2}) (?<rest>.+)$/ =~ line)
			puts "#{year} #{month} #{day} #{rest}"
		end
	}
	data
end

def get_links
	list = open($base_uri) { |f|
		Hpricot(f)
	}
	anchors = list.search("//li/a")
	links = []
	anchors.each do |anchor|
		links << anchor.attributes['href']
	end
	links
end

links = get_links
data = []
links.each { |link|
	parse_file(link)
}
#get_file links[0]
#download "http://snippets.dzone.com/posts/show/2469", "/tmp/test.out"
