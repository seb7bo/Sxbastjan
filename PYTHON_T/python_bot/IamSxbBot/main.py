from contextlib import nullcontext
from pkg_resources import to_filename
from requests import NullHandler
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
    /content -> Informacion acerca de este bot
    /contact -> Informacion de contacto 
    /paulina -> secret
    /stock APPL -> Informacion de bolsa
    /descuento -> Calcula el descuento
    """)
def content(update,context):
    update.message.reply_text("Prueba prueba prueba")
def contact(update,context):
    update.message.reply_text("Hola , Iam Sxb Bot!")

def paulina(update,context):
    update.message.reply_text("Te amo mucho paulina!")

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
    if context:
        ticker = context.args[0]
        data = web.DataReader(ticker, 'yahoo')
        price = data.iloc[-1]['Close']
        update.message.reply_text(f"el precio de las acciones {ticker} es Dolares$ {price:.2f}")
    else:
            update.message.reply_text("""
                Puedes usar stock de la siguiente forma

                /stock BTC-USD -> valor bitcoin dolares
                /stock TWTR -> valor bitcoin dolares
                /stock AAPL -> valor de bolsa Apple
                /stock NVIDIA-> valor de bolsa nvidia
                """)


#Token con clave del bot
updater = telegram.ext.Updater(TOKEN,use_context=True)

#Dispatcher de funciones
disp = updater.dispatcher


disp.add_handler(telegram.ext.CommandHandler("start",start))
disp.add_handler(telegram.ext.CommandHandler("help",help))
disp.add_handler(telegram.ext.CommandHandler("content",content))
disp.add_handler(telegram.ext.CommandHandler("contact",contact))
disp.add_handler(telegram.ext.CommandHandler("paulina",paulina))
disp.add_handler(telegram.ext.CommandHandler("stock",stock))
disp.add_handler(telegram.ext.CommandHandler("descuento",descuento))
disp.add_handler(telegram.ext.MessageHandler(telegram.ext.Filters.text,handle_message))
#Runner
updater.start_polling()
updater.idle()