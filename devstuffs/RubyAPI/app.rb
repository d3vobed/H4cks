require 'sinatra'
require 'sinatra/activerecord'
require 'bcrypt'
require 'json'

# Set up the database connection
set :database, { adapter: 'sqlite3', database: 'db/development.db' }

# Define the User model
class User < ActiveRecord::Base
  has_secure_password
end

# Create the database schema
ActiveRecord::Base.establish_connection

# Endpoint for user signup
post '/signup' do
  content_type :json
  request.body.rewind
  data = JSON.parse(request.body.read)

  username = data['username']
  password = data['password']

  # Check if the user already exists
  if User.find_by(username: username)
    status 400
    return { error: 'User already exists' }.to_json
  end

  # Create a new user
  user = User.create(username: username, password: password)

  if user.save
    status 201
    { message: 'User created successfully' }.to_json
  else
    status 500
    { error: 'User creation failed' }.to_json
  end
end

# Endpoint for user login
post '/login' do
  content_type :json
  request.body.rewind
  data = JSON.parse(request.body.read)

  username = data['username']
  password = data['password']

  user = User.find_by(username: username)

  if user && user.authenticate(password)
    status 200
    { message: 'Login successful' }.to_json
  else
    status 401
    { error: 'Invalid username or password' }.to_json
  end
end

# Create the database schema
after do
  ActiveRecord::Schema.define do
    unless table_exists? :users
      create_table :users do |t|
        t.string :username, unique: true
        t.string :password_digest
        t.timestamps
      end
    end
  end
end
