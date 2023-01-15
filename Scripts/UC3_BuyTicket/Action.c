Action()
{

	lr_start_transaction("UC3_Buy_Ticket");
	
	lr_start_transaction("open_site");
	
	web_reg_find("Fail=NotFound",
			"Text/IC=Welcome to the Web Tours site.",
			LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Not?A_Brand\";v=\"8\", \"Chromium\";v=\"108\", \"Google Chrome\";v=\"108\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

/*Correlation comment - Do not change!  Original value='135575.785014176zQHDzHQpttVzzzzHtVitcpAHzzf' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("open_site",LR_AUTO);

	lr_start_transaction("login");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",
		LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=40", ENDITEM,
		"Name=login.y", "Value=8", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("choose_flight");
	
	web_reg_find("Fail=NotFound",
			"Text/IC=Flight Selections",
			LAST);

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(26);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("choose_flight",LR_AUTO);

	lr_start_transaction("flight_detail");
	
	web_reg_save_param("outboundFlight",
				"LB/IC=outboundFlight\" value=\"",
				"RB/IC=\"",
				"Ord=ALL",
				LAST);
	
	web_reg_find("Fail=NotFound",
				"Text/IC=Flight departing from <B>{depart}</B> to <B>{arrive}</B>",
				LAST);

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(48);

/*Correlation comment - Do not change!  Original value='240;108;01/15/2023' Name ='outboundFlight' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);

	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={depart}", ENDITEM, 
		"Name=departDate", "Value={depart_date}", ENDITEM, 
		"Name=arrive", "Value={arrive}", ENDITEM, 
		"Name=returnDate", "Value={return_date}", ENDITEM, 
		"Name=numPassengers", "Value={num_passengers}", ENDITEM, 
		"Name=seatPref", "Value={seat_pref}", ENDITEM, 
		"Name=seatType", "Value={seat_type}", ENDITEM, 
		"Name=findFlights.x", "Value=42", ENDITEM, 
		"Name=findFlights.y", "Value=7", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	lr_end_transaction("flight_detail",LR_AUTO);

	lr_think_time(21);

	lr_start_transaction("departure_time");
	
	lr_save_string(lr_paramarr_random("outboundFlight"), "outboundFlight_random");

	web_submit_data("reservations.pl_2",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t5.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={outboundFlight_random}", ENDITEM,
		"Name=numPassengers", "Value={num_passengers}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={seat_type}", ENDITEM,
		"Name=seatPref", "Value={seat_pref}", ENDITEM,
		"Name=reserveFlights.x", "Value=53", ENDITEM,
		"Name=reserveFlights.y", "Value=9", ENDITEM,
		LAST);

	lr_end_transaction("departure_time",LR_AUTO);

	lr_think_time(50);

	lr_start_transaction("ticket_payment");
	
	

	web_submit_data("reservations.pl_3",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t6.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=firstName", "Value={first_name}", ENDITEM,
		"Name=lastName", "Value={last_name}", ENDITEM,
		"Name=address1", "Value={street_address}", ENDITEM,
		"Name=address2", "Value={city}", ENDITEM,
		"Name=pass1", "Value={first_name}{last_name}", ENDITEM,
		"Name=creditCard", "Value={credit_card}", ENDITEM,
		"Name=expDate", "Value=448", ENDITEM,
		"Name=oldCCOption", "Value=", ENDITEM,
		"Name=numPassengers", "Value={num_passengers}", ENDITEM,
		"Name=seatType", "Value={seat_type}", ENDITEM,
		"Name=seatPref", "Value={seat_pref}", ENDITEM,
		"Name=outboundFlight", "Value={outboundFlight_random}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=returnFlight", "Value=", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=buyFlights.x", "Value=51", ENDITEM,
		"Name=buyFlights.y", "Value=3", ENDITEM,
		"Name=.cgifields", "Value=saveCC", ENDITEM,
		LAST);

	lr_end_transaction("ticket_payment",LR_AUTO);

	lr_think_time(33);

	lr_start_transaction("flight_ticket");

	web_submit_data("reservations.pl_4", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=Book Another.x", "Value=42", ENDITEM, 
		"Name=Book Another.y", "Value=7", ENDITEM, 
		LAST);

	lr_end_transaction("flight_ticket",LR_AUTO);

	/* 2 ахкер */

//	lr_think_time(141);

//	lr_start_transaction("flight_detail");
//
//	web_submit_data("reservations.pl_5", 
//		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Method=POST", 
//		"TargetFrame=", 
//		"RecContentType=text/html", 
//		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Snapshot=t8.inf", 
//		"Mode=HTML", 
//		ITEMDATA, 
//		"Name=advanceDiscount", "Value=0", ENDITEM, 
//		"Name=depart", "Value=Denver", ENDITEM, 
//		"Name=departDate", "Value=01/15/2023", ENDITEM, 
//		"Name=arrive", "Value=Los Angeles", ENDITEM, 
//		"Name=returnDate", "Value=01/16/2023", ENDITEM, 
//		"Name=numPassengers", "Value=1", ENDITEM, 
//		"Name=seatPref", "Value=None", ENDITEM, 
//		"Name=seatType", "Value=Coach", ENDITEM, 
//		"Name=findFlights.x", "Value=46", ENDITEM, 
//		"Name=findFlights.y", "Value=5", ENDITEM, 
//		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
//		"Name=.cgifields", "Value=seatType", ENDITEM, 
//		"Name=.cgifields", "Value=seatPref", ENDITEM, 
//		LAST);
//
//	lr_end_transaction("flight_detail",LR_AUTO);
//
//	lr_think_time(22);
//
//	lr_start_transaction("departure_time");
//
//	web_submit_data("reservations.pl_6", 
//		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Method=POST", 
//		"TargetFrame=", 
//		"RecContentType=text/html", 
//		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Snapshot=t9.inf", 
//		"Mode=HTML", 
//		ITEMDATA, 
//		"Name=outboundFlight", "Value=031;224;01/15/2023", ENDITEM, 
//		"Name=numPassengers", "Value=1", ENDITEM, 
//		"Name=advanceDiscount", "Value=0", ENDITEM, 
//		"Name=seatType", "Value=Coach", ENDITEM, 
//		"Name=seatPref", "Value=None", ENDITEM, 
//		"Name=reserveFlights.x", "Value=57", ENDITEM, 
//		"Name=reserveFlights.y", "Value=7", ENDITEM, 
//		LAST);
//
//	lr_end_transaction("departure_time",LR_AUTO);

//	lr_think_time(40);
//
//	lr_start_transaction("ticket_payment");
//
//	web_submit_data("reservations.pl_7", 
//		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Method=POST", 
//		"TargetFrame=", 
//		"RecContentType=text/html", 
//		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Snapshot=t10.inf", 
//		"Mode=HTML", 
//		ITEMDATA, 
//		"Name=firstName", "Value=Ronald", ENDITEM, 
//		"Name=lastName", "Value=Weasley", ENDITEM, 
//		"Name=address1", "Value=Ottery St.Catchpole", ENDITEM, 
//		"Name=address2", "Value=Devonian", ENDITEM, 
//		"Name=pass1", "Value=Ronald Weasley", ENDITEM, 
//		"Name=creditCard", "Value=1234098745678981", ENDITEM, 
//		"Name=expDate", "Value=448", ENDITEM, 
//		"Name=oldCCOption", "Value=", ENDITEM, 
//		"Name=numPassengers", "Value=1", ENDITEM, 
//		"Name=seatType", "Value=Coach", ENDITEM, 
//		"Name=seatPref", "Value=None", ENDITEM, 
//		"Name=outboundFlight", "Value=031;224;01/15/2023", ENDITEM, 
//		"Name=advanceDiscount", "Value=0", ENDITEM, 
//		"Name=returnFlight", "Value=", ENDITEM, 
//		"Name=JSFormSubmit", "Value=off", ENDITEM, 
//		"Name=buyFlights.x", "Value=48", ENDITEM, 
//		"Name=buyFlights.y", "Value=8", ENDITEM, 
//		"Name=.cgifields", "Value=saveCC", ENDITEM, 
//		LAST);
//
//	lr_end_transaction("ticket_payment",LR_AUTO);
//
//	lr_think_time(26);
//
//	lr_start_transaction("flight_ticket");
//
//	web_submit_data("reservations.pl_8", 
//		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Method=POST", 
//		"TargetFrame=", 
//		"RecContentType=text/html", 
//		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Snapshot=t11.inf", 
//		"Mode=HTML", 
//		ITEMDATA, 
//		"Name=Book Another.x", "Value=30", ENDITEM, 
//		"Name=Book Another.y", "Value=5", ENDITEM, 
//		LAST);
//
//	lr_end_transaction("flight_ticket",LR_AUTO);
//
//	/* 3 ахкер */
//
//	lr_think_time(46);
//
//	lr_start_transaction("flight_detail");
//
//	web_submit_data("reservations.pl_9", 
//		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Method=POST", 
//		"TargetFrame=", 
//		"RecContentType=text/html", 
//		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Snapshot=t12.inf", 
//		"Mode=HTML", 
//		ITEMDATA, 
//		"Name=advanceDiscount", "Value=0", ENDITEM, 
//		"Name=depart", "Value=Sydney", ENDITEM, 
//		"Name=departDate", "Value=01/15/2023", ENDITEM, 
//		"Name=arrive", "Value=Portland", ENDITEM, 
//		"Name=returnDate", "Value=01/16/2023", ENDITEM, 
//		"Name=numPassengers", "Value=1", ENDITEM, 
//		"Name=seatPref", "Value=None", ENDITEM, 
//		"Name=seatType", "Value=Coach", ENDITEM, 
//		"Name=findFlights.x", "Value=50", ENDITEM, 
//		"Name=findFlights.y", "Value=6", ENDITEM, 
//		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
//		"Name=.cgifields", "Value=seatType", ENDITEM, 
//		"Name=.cgifields", "Value=seatPref", ENDITEM, 
//		LAST);
//
//	lr_end_transaction("flight_detail",LR_AUTO);
//
//	lr_think_time(20);
//
//	lr_start_transaction("departure_time");
//
//	web_submit_data("reservations.pl_10", 
//		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Method=POST", 
//		"TargetFrame=", 
//		"RecContentType=text/html", 
//		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Snapshot=t13.inf", 
//		"Mode=HTML", 
//		ITEMDATA, 
//		"Name=outboundFlight", "Value=851;717;01/15/2023", ENDITEM, 
//		"Name=numPassengers", "Value=1", ENDITEM, 
//		"Name=advanceDiscount", "Value=0", ENDITEM, 
//		"Name=seatType", "Value=Coach", ENDITEM, 
//		"Name=seatPref", "Value=None", ENDITEM, 
//		"Name=reserveFlights.x", "Value=50", ENDITEM, 
//		"Name=reserveFlights.y", "Value=8", ENDITEM, 
//		LAST);
//
//	lr_end_transaction("departure_time",LR_AUTO);
//
//	lr_think_time(32);

//	lr_start_transaction("ticket_payment");
//
//	web_submit_data("reservations.pl_11", 
//		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Method=POST", 
//		"TargetFrame=", 
//		"RecContentType=text/html", 
//		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
//		"Snapshot=t14.inf", 
//		"Mode=HTML", 
//		ITEMDATA, 
//		"Name=firstName", "Value=Ronald", ENDITEM, 
//		"Name=lastName", "Value=Weasley", ENDITEM, 
//		"Name=address1", "Value=Ottery St.Catchpole", ENDITEM, 
//		"Name=address2", "Value=Devonian", ENDITEM, 
//		"Name=pass1", "Value=Ronald Weasley", ENDITEM, 
//		"Name=creditCard", "Value=1234098745678981", ENDITEM, 
//		"Name=expDate", "Value=448", ENDITEM, 
//		"Name=oldCCOption", "Value=", ENDITEM, 
//		"Name=numPassengers", "Value=1", ENDITEM, 
//		"Name=seatType", "Value=Coach", ENDITEM, 
//		"Name=seatPref", "Value=None", ENDITEM, 
//		"Name=outboundFlight", "Value=851;717;01/15/2023", ENDITEM, 
//		"Name=advanceDiscount", "Value=0", ENDITEM, 
//		"Name=returnFlight", "Value=", ENDITEM, 
//		"Name=JSFormSubmit", "Value=off", ENDITEM, 
//		"Name=buyFlights.x", "Value=56", ENDITEM, 
//		"Name=buyFlights.y", "Value=4", ENDITEM, 
//		"Name=.cgifields", "Value=saveCC", ENDITEM, 
//		LAST);
//
//	lr_end_transaction("ticket_payment",LR_AUTO);

	lr_start_transaction("view_guide_sheet");

	web_reg_find("Fail=NotFound",
		"Text/IC=Flights List",
		LAST);

	web_reg_find("Fail=NotFound",
		"Text/IC={depart}  for {arrive}",
		LAST);

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(52);

/*Correlation comment - Do not change!  Original value='332638522-777-RW' Name ='flightID' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=flightID",
		"TagName=input",
		"Extract=value",
		"Name=flightID",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/itinerary.pl*",
		LAST);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("view_guide_sheet",LR_AUTO);

	lr_start_transaction("deleting_a_guide");
	

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(53);

	web_submit_data("itinerary.pl",
		"Action=http://localhost:1080/cgi-bin/itinerary.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl",
		"Snapshot=t16.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=1", "Value=on", ENDITEM,
		"Name=flightID", "Value={flightID}", ENDITEM,
//		"Name=2", "Value=on", ENDITEM,
//		"Name=flightID", "Value=332630786-1555-RW", ENDITEM,
//		"Name=3", "Value=on", ENDITEM,
//		"Name=flightID", "Value=332661174-2362-RW", ENDITEM,
		"Name=removeFlights.x", "Value=53", ENDITEM,
		"Name=removeFlights.y", "Value=8", ENDITEM,
		"Name=.cgifields", "Value=1", ENDITEM,
//		"Name=.cgifields", "Value=3", ENDITEM,
//		"Name=.cgifields", "Value=2", ENDITEM,
		LAST);

	lr_end_transaction("deleting_a_guide",LR_AUTO);

	lr_start_transaction("logout");

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(11);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t17.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("UC3_Buy_Ticket",LR_AUTO);	
		
	return 0;
}