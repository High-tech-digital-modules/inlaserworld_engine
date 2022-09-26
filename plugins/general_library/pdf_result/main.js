function generateHeader(doc) {
  const options = {
    width: doc.page.width - 40,
    align: 'right'
  }
  doc.font(regularText).fontSize(6).text('Tel: +420 734 876 767',15, 20, options)
    .text('Email: info@zabavahornik.cz', options)
    .text('Web: www.zabavahornik.cz', options)
    .text('FB: www.facebook.com/zabavnicentrumhornik', options)
    .text('Adresa: Zámecká 18, 702 00 Ostrava', options)
}

function generateGiftVoucher(doc, containerOption) {
  doc.font(boldText).text('DÁRKOVÝ POUKAZ - Chytrý a originální dárek k narozeninám',
    table3Width + table4width + 55 + doc.widthOfString('a'.repeat(20)), doc.page.height / 2, containerOption)
  doc.moveDown();
  doc.font(regularText).text('Poukazka lze využít na libovolnou aktivitu v ZC Horník', containerOption)
  doc.font(boldText).text('LASER GAME / VIRTUÁLNÍ REALITA / ARCHERY GAME', containerOption)
  doc.moveDown();
  doc.font(regularText).text('Více info na baru nebo webu', containerOption)
  doc.font(boldText).text('www.zabavahornik.cz', containerOption);
}