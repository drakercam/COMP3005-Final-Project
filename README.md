# 1. Start the PostgreSQL service
- sudo systemctl start postgresql
- sudo systemctl status postgresql

# 2. Open the Postgres shell
- sudo -u postgres psql
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