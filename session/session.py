import os
import requests
from typing import Optional, Dict, Union
from dotenv import load_dotenv

def get_42_user(identifier: Union[str, int], access_token: str) -> Optional[Dict]:
	endpoint = f"https://api.intra.42.fr/v2/users/{identifier}"
	
	headers = {
		"Authorization": f"Bearer {access_token}"
	}
	
	try:
		response = requests.get(endpoint, headers=headers)
		response.raise_for_status()
		return response.json()
	except requests.exceptions.RequestException as e:
		print(f"Error fetching user data: {e}")
		return None

def get_42_user_info(access_token: str) -> Optional[Dict]:
	endpoint = "https://api.intra.42.fr/v2/me"
	
	headers = {
		"Authorization": f"Bearer {access_token}"
	}
	
	try:
		response = requests.get(endpoint, headers=headers)
		response.raise_for_status()  # Raise exception for 4XX/5XX status codes
		return response.json()
	except requests.exceptions.RequestException as e:
		print(f"Error fetching user info: {e}")
		return None

def get_42_access_token() -> Optional[Dict]:
	load_dotenv()
	
	client_id = os.getenv('FT_CLIENT_ID')
	client_secret = os.getenv('FT_CLIENT_SECRET')
	
	if not client_id or not client_secret:
		raise ValueError("Missing required environment variables. Please set FT_CLIENT_ID and FT_CLIENT_SECRET")
	
	url = "https://api.intra.42.fr/oauth/token"
	
	headers = {
		"Content-Type": "application/x-www-form-urlencoded"
	}
	
	data = {
		"grant_type": "client_credentials",
		"client_id": client_id,
		"client_secret": client_secret
	}
	
	try:
		response = requests.post(url, headers=headers, data=data)
		response.raise_for_status()
		return response.json()
	except requests.exceptions.RequestException as e:
		print(f"Error getting access token: {e}")
		return None

def main():
	token_info = get_42_access_token()
	user = "romaurel"
	if token_info:
		access_token = token_info['access_token']
		
		user = get_42_user(user, access_token)
		if user:
			print(f"User: {user['login']}")
			print(f"Email: {user['email']}")
			print(f"Location: {user['location']}")

if __name__ == '__main__':
	main()