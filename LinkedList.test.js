import DoublyLinkedList from './DoublyLinkedList.js';

describe('DoublyLinkedList', () => {
  test('Deve inserir elementos e manter referências de head e tail', () => {
    const list = new DoublyLinkedList();
    list.insert('A', 0);
    list.insert('B', 1);

    expect(list.getHead().element).toBe('A');
    expect(list.getTail().element).toBe('B');
    // Prova da lista dupla: o anterior do tail deve ser o head
    expect(list.getTail().prev).toBe(list.getHead());
  });
});
