Cameron Drake
101325027

# Notes
- The application is programmed in C and uses libpq to connect to the PostgreSQL service.
- Ensure you have the postgres service running and link against the libpq header when building
- NOTE: The application was built and designed for Linux (I developed it on Fedora 43), so it may need some altercations to run it on Windows or Mac.

# 1. Start the PostgreSQL service
- sudo systemctl start postgresql
- sudo systemctl status postgresql

# 2. Open the Postgres shell
- sudo -u postgres psql
- DROP DATABASE gymdb;  // if exists
- CREATE DATABASE gymdb;
- \q
- close and reopen terminal

# 3. Run the DDL/DML file
Navigate to the project folder ../FinalProject/sql
Run DDL.sql and DML.sql

- sudo -u postgres psql -d gymdb -f DDL.sql
- sudo -u postgres psql -d gymdb -f DML.sql

# 4. Verify the database was created
- sudo -u postgres psql -d gymdb
- \dt

# 5. Compile the C App
- make

# 6. Run the C App
- make run

# Video Link
- https://www.youtube.com/watch?v=TtvZ_n6Uj_k