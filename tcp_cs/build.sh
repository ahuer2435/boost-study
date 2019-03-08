#! /bin/bash
rm boost_client boost_server;
g++ boost_client.cpp -lboost_system -lpthread -o boost_client
g++ boost_server.cpp -lboost_system -o boost_server
