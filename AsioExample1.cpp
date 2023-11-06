#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

int main() {

	//For errors in english
	SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));

	//Error class
	boost::system::error_code ec;

	//Platform specific interface for input/output
	boost::asio::io_context context;

	//Сайт example.com
	std::string example_ip = "93.184.216.34";
	//Localhost
	std::string local_ip = "127.0.0.1";
	//Сайт yandex.ru
	std::string yandex_ip = "5.255.255.70";

	//ip address to connect to
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address(local_ip, ec), 80);

	boost::asio::ip::tcp::socket socket(context);

	socket.connect(ep, ec);

	if (!ec) {
		std::cout << "Connected!" << std::endl;
	}
	else {
		std::cout << "Failed to connect to adress:" << std::endl << ec.message() << std::endl;
	}

	if (socket.is_open()) {

		std::string request =
			"GET /index.html HTTP/1.1\r\n"
			"Host: localhost\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(boost::asio::buffer(request, request.size()), ec);
		std::cout << "Request sent..." << std::endl;

		socket.wait(socket.wait_read);

		//std::this_thread::sleep_for(std::chrono::seconds(1));

		size_t count = socket.available();
		std::cout << "Available bytes: " << count << std::endl;

		if (count > 0) {
			std::string s;
			s.resize(count);
			socket.read_some(boost::asio::buffer(s, s.size()), ec);
			std::cout << s << std::endl;
		}
	}

	return 0;
}