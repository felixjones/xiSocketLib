# Builds all the projects in the solution...
.PHONY: all_projects
all_projects: xiSock example.01.client example.01.server example.02.client example.02.server example.03.broadcast 

# Builds project 'xiSock'...
.PHONY: xiSock
xiSock: 
	make --directory="." --file=xiSock.makefile

# Builds project 'example.01.server'...
.PHONY: example.01.server
example.01.server: xiSock 
	make --directory="." --file=example.01.server.makefile

# Builds project 'example.01.client'...
.PHONY: example.01.client
example.01.client: xiSock 
	make --directory="." --file=example.01.client.makefile

# Builds project 'example.02.client'...
.PHONY: example.02.client
example.02.client: xiSock 
	make --directory="." --file=example.02.client.makefile

# Builds project 'example.02.server'...
.PHONY: example.02.server
example.02.server: xiSock 
	make --directory="." --file=example.02.server.makefile

# Builds project 'example.03.broadcast'...
.PHONY: example.03.broadcast
example.03.broadcast: xiSock 
	make --directory="." --file=example.03.broadcast.makefile

# Cleans all projects...
.PHONY: clean
clean:
	make --directory="." --file=xiSock.makefile clean
	make --directory="." --file=example.01.server.makefile clean
	make --directory="." --file=example.01.client.makefile clean
	make --directory="." --file=example.02.client.makefile clean
	make --directory="." --file=example.02.server.makefile clean
	make --directory="." --file=example.03.broadcast.makefile clean

