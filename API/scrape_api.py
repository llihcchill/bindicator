from flask import Flask
import web_scrape
import json

app = Flask(__name__)

@app.route("/", methods=["GET"])
def website_scrape():
    
    # web scrape the councils website
    web_scrape.scrape("my councils website (doesn't really work with other ones but fork this repo and do a bit of adjusting and it should work)", "your address")
    return web_scrape.bin_output

if __name__ == "__main__":
    app.run(port=8080, debug=true, host='0.0.0.0')
