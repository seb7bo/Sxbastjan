
import telegram.ext
import pandas_datareader as web


with open('token.txt','r') as f:
    TOKEN = f.read()

#Funciones
def start(update,context):
    update.message.reply_text("Hola , Bienvenido a IamSxbBot!")

def help(update,context):
    update.message.reply_text("""
    Los siguientes comandos estan disponibles:

    /start -> mensaje de bienvenida
    /help -> este mensaje
    /contact -> Informacion de contacto 
    /stock -> Informacion de bolsa
    /descuento -> Calcula el descuento
    """)

def contact(update,context):
    update.message.reply_text("Hola , Iam Sxb Bot!")


def handle_message(update,context):
    update.message.reply_text(f"Tu dijiste {update.message.text}")

def descuento(update,context):
    string_valores= context.args[0]
    print(string_valores)
    valores = string_valores.split()
    print(valores)
    precio = int(valores[0])
    print(precio)
    descuento = int(valores[1])
    print(descuento)
    precio_final = precio -(precio *  (descuento/100)) 
    update.message.reply_text(f"el descuento {descuento} tu prenda va de {precio} a {precio_final}")


def stock(update,context): 
    update.message.reply_text("""
        Puedes usar stock de la siguiente forma

        /stock_BTC-USD -> valor bitcoin dolares
        /stock_TWTR -> valor Twitter dolares
        /stock_AAPL -> valor de bolsa Apple
        /stock_NVDA-> valor de bolsa nvidia
        /stock_FB -> valor de bolsa Facebook
        """)


def stock_AAPL(update,context):
    ticker = 'AAPL'
    data = web.DataReader(ticker, 'yahoo')
    price = data.iloc[-1]['Close']
    update.message.reply_text(f"el precio de las acciones {ticker} es Dolares$ {price:.2f}")

def stock_BTC_USD(update,context):
    ticker = 'BTC-USD'
    data = web.DataReader(ticker, 'yahoo')
    price = data.iloc[-1]['Close']
    update.message.reply_text(f"el precio de las acciones {ticker} es Dolares$ {price:.2f}")

def stock_TWTR(update,context):
    ticker = 'TWTR'
    data = web.DataReader(ticker, 'yahoo')
    price = data.iloc[-1]['Close']
    update.message.reply_text(f"el precio de las acciones {ticker} es Dolares$ {price:.2f}")

def stock_FB(update,context):
    ticker = 'FB'
    data = web.DataReader(ticker, 'yahoo')
    price = data.iloc[-1]['Close']
    update.message.reply_text(f"el precio de las acciones {ticker} es Dolares$ {price:.2f}")

#Token con clave del bot
updater = telegram.ext.Updater(TOKEN,use_context=True)

#Dispatcher de funciones
disp = updater.dispatcher


disp.add_handler(telegram.ext.CommandHandler("start",start))
disp.add_handler(telegram.ext.CommandHandler("help",help))
disp.add_handler(telegram.ext.CommandHandler("contact",contact))


# Stock functions
disp.add_handler(telegram.ext.CommandHandler("stock_AAPL",stock_AAPL))
disp.add_handler(telegram.ext.CommandHandler("stock_FB",stock_FB))
disp.add_handler(telegram.ext.CommandHandler("stock_FB",stock_FB))
disp.add_handler(telegram.ext.CommandHandler("stock_TWTR",stock_TWTR))
disp.add_handler(telegram.ext.CommandHandler("stock_BTC_USD",stock_BTC_USD))

# descuento
disp.add_handler(telegram.ext.CommandHandler("descuento",descuento))


disp.add_handler(telegram.ext.MessageHandler(telegram.ext.Filters.text,handle_message))
#Runner
updater.start_polling()
updater.idle()


import telegram.ext
import pandas_datareader as web


with open('token_Server.txt','r') as f:
    TOKEN1 = f.read()

with open('token_Client')