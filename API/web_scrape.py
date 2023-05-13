import selenium
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.service import Service as ChromeService
from webdriver_manager.chrome import ChromeDriverManager
from selenium.common.exceptions import NoSuchElementException
from selenium.common.exceptions import StaleElementReferenceException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions

def scrape(url, address):
    # start the driver and load the url to web scrape
    driver = webdriver.Chrome(service=ChromeService(ChromeDriverManager().install()))
    driver.get(str(url))

    # find the iframe element which contains the input wanted
    iframe = driver.find_element(By.TAG_NAME, "iframe")
    driver.switch_to.frame(iframe)

    # find the element with the id "addressInput" and input the selected address
    driver.find_element(By.ID, "addressInput").send_keys(address)
    ignored_exceptions=(NoSuchElementException,StaleElementReferenceException)
    address_dropdown = WebDriverWait(driver, 80, ignored_exceptions=ignored_exceptions).until(expected_conditions.presence_of_element_located((By.ID, f"{address},3,3,B")))
    driver.find_element(By.ID, f"{address},3,3,B").click()

    # get the output of the address input
    general_waste_text = driver.find_element(By.CLASS_NAME, "generalWasteBox").text
    recycling_text = driver.find_element(By.CLASS_NAME, "recyclingBox").text

    # split generalWaste_text and recycling_text into each seperate word
    gw_split = general_waste_text.split()
    re_split = recycling_text.split()

    # call get_date function to get the date that the bins need to be put out
    get_date(gw_split, re_split)

def get_date(garbage_split_text, recycling_split_text):
    # makes sure to edit the global bin_dict variable for it to show up in the output of the API
    global bin_dict
    # this function checks against the supplied split text to see if their dates line up
    if garbage_split_text[7] == recycling_split_text[6]:
        bin_dict = [
            {
            "bins_out": "2"
            }
        ]
    else:
        bin_dict = [
            {
            "bins_out": "1"
            }
        ]
