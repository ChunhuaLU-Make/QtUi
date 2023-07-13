# encoding: utf-8
#import docx
#from openpyxl import Workbook

doc = docx_m.Document(fileName)


wb = excel_mod.Workbook()
ws = wb.active

count = 1
AL = 'A'
BL = 'B'
CL = 'C'
DL = 'D'
EL = 'E'
FL = 'F'
GL = 'G'
HL = 'H'
IL = 'I'


for para in doc.paragraphs:
    if para.style.name.startswith("Heading 1"):
        AL += str(count)
        ws[AL] = para.text
        count+=1
        AL = 'A'
        msg = 'leve1' +para.text
        DocxSwitchExcelCbk(msg)

    elif para.style.name.startswith("Heading 2"):
        BL+=str(count)
        ws[BL] = para.text
        count+=1
        BL = 'B'
        msg = 'leve2:'+para.text
        DocxSwitchExcelCbk(msg)

    elif para.style.name.startswith("Heading 3"):
        CL+=str(count)
        ws[CL] = para.text
        count+=1
        CL = 'C'
        msg ='leve2:'+para.text
        DocxSwitchExcelCbk(msg)

    elif para.style.name.startswith("Heading 4"):
        DL+=str(count)
        ws[DL] = para.text
        count+=1
        DL = 'D'
        msg ='leve4:'+para.text
        DocxSwitchExcelCbk(msg)

    elif para.style.name.startswith("Heading 5"):
        EL+=str(count)
        ws[EL] = para.text
        count+=1
        EL = 'E'
        msg ='leve5:'+para.text
        DocxSwitchExcelCbk(msg)


    elif para.style.name.startswith("Heading 6"):
        FL+=str(count)
        ws[FL] = para.text
        count+=1
        FL = 'F'
        msg ='leve6:'+para.text
        DocxSwitchExcelCbk(msg)

    elif para.style.name.startswith("Heading 7"):
        GL+=str(count)
        ws[GL] = para.text
        count+=1
        GL = 'G'
        msg ='leve7:'+para.text
        DocxSwitchExcelCbk(msg)


    elif para.style.name.startswith("Heading 8"):
        HL+=str(count)
        ws[HL] = para.text
        count+=1
        HL = 'H'
        msg ='leve8:'+para.text
        DocxSwitchExcelCbk(msg)

    elif para.style.name.startswith("Heading 9"):
        IL+=str(count)
        ws[IL] = para.text
        count+=1
        IL = 'I'
        msg ='leve9:'+para.text
        DocxSwitchExcelCbk(msg)


wb.save("output.xlsx")

